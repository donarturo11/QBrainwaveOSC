#ifndef BRAINWAVE_DEVICECONNECTION_H
#define BRAINWAVE_DEVICECONNECTION_H
#include <QObject>
#include <QtCore>
#include <typeinfo>
#include <typeindex>
#include "DataParser.h"

namespace Brainwave {
namespace Device {
typedef enum {
    ConnectionFailed = -1,
    NoConnected,
    Idle,
    Connected,
    Reading,
    Writing
} ConnectionStatus;
}
class DeviceConnection : public QObject
{
    Q_OBJECT
public:
    DeviceConnection(QObject *parent = nullptr) : QObject(parent)
    {
        _status = Device::ConnectionStatus::NoConnected;
    }
    virtual void setupConnection(QVariantMap) = 0;
    virtual void open() {
        connect(_dev, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        _dev->open(QIODeviceBase::ReadWrite);
    }
    virtual void close() {
        disconnect(_dev, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        _dev->close();
        }
    const Device::ConnectionStatus connectionStatus() {return _status;}
    Device::ConnectionStatus _status;
    QIODevice *_dev; /* QSerialPort, QBuffer, QBluetoothSocket */
public slots:
    void onBytesReceived(qint64 numbytes) {
        qDebug() << "Received" << numbytes << "bytes";
        QByteArray d = _dev->read(numbytes);
        emit bytesReceived(d.data(), numbytes);
    }
    void onReadyRead() {
        int numbytes = _dev->bytesAvailable();
        QByteArray d = _dev->read(numbytes);
        emit bytesReceived(d.data(), numbytes);
    }
signals:
    void connectionStatusChanged(Device::ConnectionStatus _status);
    void bytesReceived(const char*, int);


};

}
#endif
