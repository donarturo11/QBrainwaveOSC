#include "DeviceDiscovery.h"
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

DeviceDiscovery::DeviceDiscovery(QObject *parent) :
    QObject(parent)
{
    connect (&bt_agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
             this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo)));
}

DeviceDiscovery::~DeviceDiscovery()
{
}

void DeviceDiscovery::refresh()
{
    qDebug() << "Called DeviceDiscovery::refresh";
    bt_agent.stop();
    bt_agent.start();
}

void DeviceDiscovery::start()
{
    bt_agent.start();
}

void DeviceDiscovery::stop()
{
    bt_agent.stop();
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
    stop();
}
