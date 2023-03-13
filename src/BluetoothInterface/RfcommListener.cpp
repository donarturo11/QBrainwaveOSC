#include "RfcommListener.h"

RfcommListener::RfcommListener(QObject *parent) :
    QObject(parent)
{
    qDebug() << "RfcommListener c-tor";
    status = ConnectionStatus::DISCONNECTED;
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->setTextModeEnabled(false);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

RfcommListener::~RfcommListener()
{

}

void RfcommListener::connectService(QBluetoothServiceInfo& remoteService)
{
    socket->connectToService(remoteService);
}

void RfcommListener::disconnectService()
{
   qDebug() << "RfcommListener::disconnect()";
   socket->disconnectFromService();
}

void RfcommListener::readData()
{
    auto data = socket->read(1);
    emit receivedData(data);
}

void RfcommListener::writeData()
{

}