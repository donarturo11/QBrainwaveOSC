#include "BluetoothManager.h"

BluetoothManager* BluetoothManager::currentInstance;

BluetoothManager::BluetoothManager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "BluetoothManager c-tor";
    connect(&dev_discovery, SIGNAL(finished()), this, SLOT(updateDevicesList()));
    BluetoothManager::currentInstance = this;
}

BluetoothManager::~BluetoothManager()
{
    //if(currentInstance) delete currentInstance;
}

void BluetoothManager::refreshDevices()
{
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
    qDebug() << "connect to " << currentRemoteDevice.name() << " "
             << currentRemoteDevice.address().toString();
}

void BluetoothManager::disconnectDevice()
{
    qDebug() << "disconnect";
}

void BluetoothManager::setup(QString address)
{
    qDebug() << "setup address: " << address;
    QBluetoothAddress btAddress(address);
    for (auto dev : bt_devices) {
        if (dev.address()==btAddress) {
            qDebug() << dev.name();
            currentRemoteDevice = dev;
            break;
        }
    }
    ServiceDiscovery discovery(currentRemoteDevice.address(), this);
    qDebug() << discovery.getServicesList();
}