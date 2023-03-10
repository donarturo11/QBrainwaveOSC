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
    connect(discoveryAgent, SIGNAL(serviceDiscovered(const QBluetoothServiceInfo)),
            this, SLOT(addService(const QBluetoothServiceInfo &info)));
    //connect(discoveryAgent, SIGNAL(finished()),
    //        this, SLOT(onFinished()));
}

ServiceDiscovery::~ServiceDiscovery()
{
    delete discoveryAgent;
}

void ServiceDiscovery::start()
{
    discoveryAgent->start();
}

void ServiceDiscovery::stop()
{
    discoveryAgent->stop();
    qDebug() << "Stop";
}

void ServiceDiscovery::addService(const QBluetoothServiceInfo &info)
{
    if (info.serviceName().isEmpty())
        return;

    QString line = info.serviceName();
    if (!info.serviceDescription().isEmpty())
        line.append("\n\t" + info.serviceDescription());
    if (!info.serviceProvider().isEmpty())
        line.append("\n\t" + info.serviceProvider());

    qDebug() << line;
}


void ServiceDiscovery::onFinished()
{
    stop();
}
