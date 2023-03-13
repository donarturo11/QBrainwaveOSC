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
    connect (bt_agent, SIGNAL(finished()),
             this, SLOT(onDeviceDiscoveryFinished()));
    connect (bt_agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
             this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo)));
}

DeviceDiscovery::~DeviceDiscovery()
{
    delete bt_agent;
}

void DeviceDiscovery::refresh()
{
    qDebug() << "Called DeviceDiscovery::refresh";
    bt_agent->stop();
    bt_agent->start();
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
}

void DeviceDiscovery::stop()
{
    bt_agent->stop();
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
    qDebug() << "bt_devices contains " << info.name() << ":" << bt_devices.contains(info);
    if (bt_devices.contains(info)) return;
    bt_devices << info;
    emit deviceDiscovered(info);
}
void DeviceDiscovery::onDeviceDiscoveryFinished()
{
    search();
    stop();
}
