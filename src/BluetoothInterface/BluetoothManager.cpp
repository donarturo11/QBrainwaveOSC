#include "BluetoothManager.h"

BluetoothManager* BluetoothManager::currentInstance;

BluetoothManager::BluetoothManager(QObject *parent) :
    QObject(parent)
    , setupReady(false)
{
    qDebug() << "BluetoothManager c-tor";
    localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    //connect(&dev_discovery, SIGNAL(finished()), this, SLOT(updateDevicesList()));
    connect(&dev_discovery, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
             this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo)));
    BluetoothManager::currentInstance = this;
}

BluetoothManager::~BluetoothManager()
{
    //if(currentInstance) delete currentInstance;
}

void BluetoothManager::startDeviceDiscovery()
{
    dev_discovery.start();
}

void BluetoothManager::stopDeviceDiscovery()
{
    dev_discovery.stop();
}

void BluetoothManager::onDeviceDiscovered(const QBluetoothDeviceInfo &info)
{
    qDebug() << "[BluetoothManager] onDeviceDiscovered";
    if (!bt_devices.contains(info))
        bt_devices << info;
    emit deviceDiscovered(info);
}

void BluetoothManager::refreshDevices()
{
    qDebug() << "Refresh devices";
    dev_discovery.refresh();
}

void BluetoothManager::updateDevicesList()
{
    qDebug() << "update devices list";
    bt_devices = dev_discovery.getDevicesList();
    emit deviceDiscoveryFinished();
}

void BluetoothManager::connectDevice()
{
    try {
        qDebug() << "Connecting to  " << currentRemoteDevice.name() << " "
             << currentRemoteDevice.address().toString();
        if (!setupReady) throw BluetoothManagerError();
        dev_discovery.stop();
        bt_listener.connectService(currentRemoteService);
    } catch (BluetoothManagerError &e) {
        qDebug() << "Connection error ";
    }
    qDebug() << "Connection established";
}

void BluetoothManager::disconnectDevice()
{
    qDebug() << "disconnect";
    bt_listener.disconnectService();
}

void BluetoothManager::setup(QString addressStr)
{
    QBluetoothAddress address(addressStr);
    setupDevice(address);
    setupService();
}

void BluetoothManager::setupDevice(QBluetoothAddress address)
{
    qDebug() << "setup address: " << address;
    for (auto dev : bt_devices) {
        if (dev.address()==address) {
            qDebug() << dev.name();
            currentRemoteDevice = dev;
            break;
        }
    }    
}

void BluetoothManager::setupService()
{
    ServiceDiscovery discovery(currentRemoteDevice.address(), this);
    bt_services = discovery.getServicesList();
    for (auto s : bt_services) {
        if (rfcommEnabled(s)) {
            currentRemoteService = s;
            setupReady = true;
            break;
        }
    }
    
}

bool BluetoothManager::rfcommEnabled(const QBluetoothServiceInfo &serviceInfo)
{
    auto uuids = serviceInfo.serviceClassUuids();
    for (auto uuid : uuids)
        if (uuid.data1==0x1101) return true;
    return false;
}