#include "RfcommListener.h"

RfcommListener::RfcommListener(QObject *parent) :
    QObject(parent),
    running(false)
{
    qDebug() << "RfcommListener c-tor";
}

RfcommListener::~RfcommListener()
{
}

void RfcommListener::connectService(QBluetoothServiceInfo& remoteService)
{
    if (running) return;
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(remoteService);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    running = true;
}

void RfcommListener::disconnectService()
{
   if (!running) return;
   qDebug() << "RfcommListener::disconnect()";
   disconnect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
   socket->disconnectFromService();
   delete socket;
   running = false;
}

void RfcommListener::readData()
{
    auto data = socket->read(1);
    qDebug() << "received data: " << data;
    emit receivedData(data);
}

void RfcommListener::writeData()
{

}
