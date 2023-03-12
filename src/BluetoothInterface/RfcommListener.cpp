#include "RfcommListener.h"

RfcommListener::RfcommListener(QObject *parent) :
    QObject(parent)
{
    qDebug() << "RfcommListener c-tor";
    status = ConnectionStatus::DISCONNECTED;
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
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
    const char *data = socket->read(1);
    if (*data == 0xAA) printf("\n");
    printf("x%X ", *data);
}

void RfcommListener::writeData()
{

}