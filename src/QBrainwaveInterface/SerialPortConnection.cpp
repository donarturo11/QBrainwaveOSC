#include "SerialPortConnection.h"
namespace Brainwave {

SerialPortConnection::SerialPortConnection(QObject *parent)
 : DeviceConnection(parent)
{
    _dev = new QSerialPort(this);
}

SerialPortConnection::~SerialPortConnection()
{
    disconnect(this, nullptr, this, nullptr);
    if (_dev) delete _dev;
}

void SerialPortConnection::setupConnection(QVariantMap args)
{
    device()->setPortName(QVariant(args["portname"]).toString());
    device()->setBaudRate(QVariant(args["baudrate"]).toInt());
    auto deviceType = args["type"].toString();
    if (deviceType == "ThinkGearStreamParser") {
        connect(this, &DeviceConnection::connectionStatusChanged,
                [this](Brainwave::Device::ConnectionStatus status) {
                    switch(status) {
                        case Device::ConnectionStatus::Connected:
                            qDebug() << "Connecting ThinkGear";
                            device()->write("\xc2", 1);
                            device()->flush();
                            break;
                        case Device::ConnectionStatus::Disconnecting:
                            qDebug() << "Disconnecting ThinkGear";
                            device()->write("\xc1", 1);
                            device()->flush();
                            break;
                    }
                });
    }
}

void SerialPortConnection::onDeviceIsClosing()
{
    //while (device()->flush());
}

}
