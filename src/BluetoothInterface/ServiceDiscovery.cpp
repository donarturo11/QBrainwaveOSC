#include "ServiceDiscovery.h"
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

ServiceDiscovery::ServiceDiscovery(const QBluetoothAddress &address, QObject *parent) :
    QObject(parent)
{
    qDebug() << "ServiceDiscovery c-tor";
    QBluetoothLocalDevice localDevice;
    QBluetoothAddress adapterAddress = localDevice.address();
    discoveryAgent = new QBluetoothServiceDiscoveryAgent(adapterAddress);
    discoveryAgent->setRemoteAddress(address);
    connect(discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(onServiceDiscovered(QBluetoothServiceInfo)));
    connect(discoveryAgent, SIGNAL(finished()),
            this, SLOT(onFinished()));
}

ServiceDiscovery::~ServiceDiscovery()
{
    if (discoveryAgent && !discoveryAgent->isActive())
        delete discoveryAgent;
}

void ServiceDiscovery::updateServicesList()
{
    discoveryAgent->start();
}

void ServiceDiscovery::onServiceDiscovered(const QBluetoothServiceInfo &info)
{
    detectedServices << info;
    emit serviceDiscovered(info);
}


void ServiceDiscovery::onFinished()
{
    discoveryAgent->stop();
    emit serviceDiscoveryFinished();
}
