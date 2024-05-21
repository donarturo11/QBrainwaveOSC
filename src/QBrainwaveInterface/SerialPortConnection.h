#ifndef BRAINWAVE_SERIALPORTCONNECTION_H
#define BRAINWAVE_SERIALPORTCONNECTION_H
#include <QObject>
#include <QtCore>
#include <QSerialPort>
#include <QStringList>
#include "DeviceConnection.h"
#include "DataParser.h"

namespace Brainwave {

class SerialPortConnection : public DeviceConnection
{
public:
    SerialPortConnection(QObject *parent = nullptr);
    ~SerialPortConnection();
    void open();
    void close();
private:
    QSerialPort* device() { return reinterpret_cast<QSerialPort*>(_dev); }
protected:

};

} // namespace Brainwave
#endif
