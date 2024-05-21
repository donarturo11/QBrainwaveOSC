#ifndef BRAINWAVE_DEVICECONNECTION_H
#define BRAINWAVE_DEVICECONNECTION_H
#include <QObject>
#include <QtCore>
#include <typeinfo>
#include <typeindex>
#include "DataParser.h"

namespace Brainwave {
typedef enum {
    ConnectionFailed = -1,
    NoConnected,
    Idle,
    Connected,
    Reading,
    Writing
} ConnectionStatus;

class DeviceConnection : public QObject
{
public:
    DeviceConnection(QObject *parent = nullptr) : QObject(parent)
    {
        _status = ConnectionStatus::NoConnected;
    }
    virtual void open() = 0;
    virtual void close() = 0;
    virtual const std::type_index connection_type() = 0; // { return typeid(DeviceConnection); }
    const ConnectionStatus connectionStatus() {return _status;}
    ConnectionStatus _status;
    QIODevice *_dev; /* QSerialPort, QBuffer, QBluetoothSocket */
signals:
    void connectionStatusChanged(ConnectionStatus _status);


};

}
#endif