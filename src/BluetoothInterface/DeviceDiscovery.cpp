#include "DeviceDiscovery.h"
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

DeviceDiscovery::DeviceDiscovery(QObject *parent) :
    QObject(parent)
{
    qDebug() << "DeviceDiscovery c-tor";
    bt_agent = new QBluetoothDeviceDiscoveryAgent(this);
    connect (bt_agent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo)),
             this, SLOT(onDeviceDiscovered(const QBluetoothDeviceInfo)));
    bt_agent->start();
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
    qDebug() << "BT Devices size: " << bt_devices.size();
}

void DeviceDiscovery::start()
{
    qDebug() << "Init agent";

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
    for (auto dev : bt_agent->discoveredDevices()) {
        qDebug() << dev.name() << " " << dev.address() << " " << dev.isValid();
    }
    updateList();
    emit finished();
    //clear();
}

void DeviceDiscovery::onDeviceDiscovered(const QBluetoothDeviceInfo &info)
{
     if (bt_devices.contains(info)) return;
     bt_devices << info;
     emit updated(info);
}