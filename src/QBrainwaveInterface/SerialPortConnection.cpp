#include "SerialPortConnection.h"
namespace Brainwave {

SerialPortConnection::SerialPortConnection(QObject *parent)
 : DeviceConnection(parent)
{
    _dev = new QSerialPort(this);
    qDebug() << "SerialPortConnection c-tor";
}

SerialPortConnection::~SerialPortConnection()
{
    qDebug() << "SerialPortConnection d-tor";
}

void SerialPortConnection::open()
{
    qDebug() << __FUNCTION__;
}

void SerialPortConnection::close()
{
    qDebug() << __FUNCTION__;
}

}