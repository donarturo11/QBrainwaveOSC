#include "RfcommListener.h"

RfcommListener::RfcommListener(QObject *parent) :
    QObject(parent)
{
    qDebug() << "RfcommListener c-tor";
    status = ConnectionStatus::DISCONNECTED;
    bt_uuid = QBluetoothUuid(QBluetoothUuid::ProtocolUuid::Rfcomm);
    rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
    rfcommServer->listen(localDevice.address());
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    port = rfcommServer->serverPort();
    bt_uuid = QBluetoothUuid(QBluetoothUuid::ProtocolUuid::Rfcomm);
    qDebug() << "Server port " << port;
    qDebug() << localDevice.connectedDevices();
}

RfcommListener::~RfcommListener()
{

}

void RfcommListener::connect(QString address)
{
    //if(address_) delete address_;
    //qDebug() << "RfcommListener::connect(" << address << ")";
    remoteAddress = QBluetoothAddress(address);
    
    
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
