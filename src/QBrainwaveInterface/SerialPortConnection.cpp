#include "SerialPortConnection.h"
namespace Brainwave {

SerialPortConnection::SerialPortConnection(QObject *parent)
 : DeviceConnection(parent)
{
    _dev = new QSerialPort(this);
}

SerialPortConnection::~SerialPortConnection()
{
    if (_dev) delete _dev;
}

void SerialPortConnection::setupConnection(QVariantMap args)
{
    device()->setPortName(QVariant(args["portname"]).toString());
    device()->setBaudRate(QVariant(args["baudrate"]).toInt());
}

}
