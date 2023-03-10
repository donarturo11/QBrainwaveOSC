#include "BluetoothDiscovery.h"
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

BluetoothDiscovery::BluetoothDiscovery(QObject *parent) :
    QObject(parent)
{
    qDebug() << "BluetoothDiscovery c-tor";
}

BluetoothDiscovery::~BluetoothDiscovery()
{

}

void BluetoothDiscovery::refresh()
{
    start();
}

void  BluetoothDiscovery::updateList()
{
    if (!bt_agent) return;
    bt_devices = bt_agent->discoveredDevices();
}

void BluetoothDiscovery::start()
{
    qDebug() << "Start";
    if (!bt_devices.empty()) bt_devices.clear();
    qDebug() << "Init agent";
    bt_agent = new QBluetoothDeviceDiscoveryAgent();
    bt_agent->start();
    search();
}

void BluetoothDiscovery::stop()
{
    qDebug() << "Stop";
}

void BluetoothDiscovery::clear()
{
    if (!bt_agent) return;
    delete bt_agent;
}

void BluetoothDiscovery::search()
{
    qDebug() << "Searching " << bt_agent->isActive();
    for (auto dev : bt_agent->discoveredDevices()) {
        qDebug() << dev.name() << " " << dev.address() << " " << dev.isValid();
    }
    updateList();
    emit finished();
    clear();
}

