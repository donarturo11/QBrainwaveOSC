#include "DeviceDiscovery.h"
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

DeviceDiscovery::DeviceDiscovery(QObject *parent) :
    QObject(parent)
{
    qDebug() << "DeviceDiscovery c-tor";
}

DeviceDiscovery::~DeviceDiscovery()
{

}

void DeviceDiscovery::refresh()
{
    start();
}

void  DeviceDiscovery::updateList()
{
    if (!bt_agent) return;
    bt_devices = bt_agent->discoveredDevices();
}

void DeviceDiscovery::start()
{
    qDebug() << "Start";
    if (!bt_devices.empty()) bt_devices.clear();
    qDebug() << "Init agent";
    bt_agent = new QBluetoothDeviceDiscoveryAgent();
    bt_agent->start();
    search();
}

void DeviceDiscovery::stop()
{
    qDebug() << "Stop";
}

void DeviceDiscovery::clear()
{
    if (!bt_agent) return;
    delete bt_agent;
}

void DeviceDiscovery::search()
{
    qDebug() << "Searching devices...";
    //for (auto dev : bt_agent->discoveredDevices()) {
    //    qDebug() << dev.name() << " " << dev.address() << " " << dev.isValid();
    //}
    updateList();
    emit finished();
    clear();
}

