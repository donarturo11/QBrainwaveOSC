#include "BluetoothManager.h"

BluetoothManager* BluetoothManager::currentInstance;

BluetoothManager::BluetoothManager(QObject *parent) :
    QObject(parent),
    setupReady(false)
{
    qDebug() << "BluetoothManager c-tor";
    localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
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
    
    if (!bt_devices.contains(info))
        bt_devices << info;
    emit deviceDiscovered(info);
}

void BluetoothManager::startServiceDiscovery()
{
    srv_discovery = new ServiceDiscovery(currentRemoteDevice.address(), this);
    connect(srv_discovery, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(onServiceDiscovered(QBluetoothServiceInfo)));
    connect(this, SIGNAL(serviceFound()),
            this, SLOT(onServiceDiscoveryFinished()));
    srv_discovery->updateServicesList();
}

void BluetoothManager::stopServiceDiscovery()
{
    if (srv_discovery) {
        delete srv_discovery;
    }
}


void BluetoothManager::onServiceDiscovered(const QBluetoothServiceInfo &info)
{
    qDebug() << "[BluetoothManager] onServiceDiscovered";
    if (serialPortEnabled(info)) {
        currentRemoteService = info;
        setupReady = true; 
        qDebug() << "[BluetoothManager] Serial Port found successfully";
        emit serviceFound();
        stopServiceDiscovery();
    } else {
        setupReady = false;
        qDebug() << "[BluetoothManager] Serial Port found FAILED";
    }
}

void BluetoothManager::onServiceDiscoveryFinished()
{
    qDebug() << "[BluetoothManager] Service Discovery finished";
    //stopServiceDiscovery();
}

void BluetoothManager::refreshDevices()
{
    qDebug() << "Refresh devices";
    dev_discovery.refresh();
}

void BluetoothManager::connectDevice()
{
    try {
        qDebug() << "Connecting to  " << currentRemoteDevice.name() << " "
             << currentRemoteDevice.address().toString();
        if (!setupReady) throw BluetoothManagerError();
        dev_discovery.stop();
        bt_listener.connectService(currentRemoteService);
        qDebug() << "Connection established";
    } catch (BluetoothManagerError &e) {
        qDebug() << "Connection error ";
    }
    
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
    startServiceDiscovery();
}

bool BluetoothManager::serialPortEnabled(const QBluetoothServiceInfo &serviceInfo)
{
    auto uuids = serviceInfo.serviceClassUuids();
    for (auto uuid : uuids)
        if (uuid.data1==0x1101) return true;
    return false;
}