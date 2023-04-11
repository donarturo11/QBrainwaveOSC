#include "ThinkGear.h"

ThinkGear::ThinkGear(QObject *parent) :
    QObject(parent)
{
    qDebug() << "ThinkGear c-tor";
    connect(&device, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    device.setReadBufferSize(512);
}

ThinkGear::~ThinkGear()
{

}

void ThinkGear::open()
{
    qDebug() << "ThinkGear: connect to : "
             << device.portName() << "@" 
             << device.baudRate();
    bool opened = device.open(QIODeviceBase::ReadWrite);
    if (opened) qDebug() << "Open SUCCESS";
    else qDebug() << "Open FAILED";
}

void ThinkGear::close()
{
    qDebug() << "ThinkGear::disconnect";
    device.flush();
    device.close();
}

void ThinkGear::onReadyRead()
{
    qDebug() << "[ThinkGear] readData " << device.readBufferSize();
    auto data = device.read(device.readBufferSize());
    emit receivedData(data);
}