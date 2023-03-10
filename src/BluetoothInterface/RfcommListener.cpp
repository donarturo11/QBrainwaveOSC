#include "RfcommListener.h"

RfcommListener::RfcommListener(QObject *parent) :
    QObject(parent)
{
    qDebug() << "RfcommListener c-tor";
    status = ConnectionStatus::DISCONNECTED;
    bt_uuid = QBluetoothUuid(QBluetoothUuid::ProtocolUuid::Rfcomm);
}

RfcommListener::~RfcommListener()
{

}

void RfcommListener::connect(QString address)
{
    //if(address_) delete address_;
    //qDebug() << "RfcommListener::connect(" << address << ")";
    QBluetoothServiceInfo serviceInfo;
    deviceAddress = QBluetoothAddress(address);
    QBluetoothServiceDiscoveryAgent serviceAgent(deviceAddress, this);
    serviceAgent.start();
    serviceAgent.stop();
    auto services = serviceAgent.discoveredServices();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    for (auto s : services) {
        qDebug() << s.socketProtocol();
        if (s.socketProtocol() == QBluetoothServiceInfo::RfcommProtocol) {
            socket->connectToService(s);
            break;
        }
    }
    
    
}

void RfcommListener::disconnect()
{
   qDebug() << "RfcommListener::disconnect()";
}

void RfcommListener::onDisconnectionRequest()
{
    disconnect();
}

void RfcommListener::onConnectionRequest(QString address)
{
    connect(address);
}