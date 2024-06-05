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
    if (_dev) delete _dev;
}

void SerialPortConnection::setupConnection(QVariantMap args)
{
    qDebug() << "SerialPortConnection:" << __FUNCTION__;
    qDebug() << "args:";
    device()->setPortName(QVariant(args["portname"]).toString());
    device()->setBaudRate(QVariant(args["baudrate"]).toInt());
    //device()->setFlowControl(QSerialPort::HardwareControl);
    qDebug() << "Setup:" << device()->portName() << "@" << device()->baudRate();
}

}
