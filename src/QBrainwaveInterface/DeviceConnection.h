#ifndef BRAINWAVE_DEVICECONNECTION_H
#define BRAINWAVE_DEVICECONNECTION_H
#include <QObject>
#include <QtCore>
#include <QHash>
#include <typeinfo>
#include <typeindex>
#include "DataParser.h"
#include "ConnectionStatus.h"

namespace Brainwave {

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
        #ifdef QT6
            auto open_opt = QIODeviceBase::ReadWrite;
        #else
            auto open_opt = QIODevice::ReadWrite;
        #endif
        if(_dev->open(open_opt)) {
            connect(_dev, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
            _status = Device::ConnectionStatus::Connected;
            emit connectionStatusChanged(_status);
        } else {
            _status = Device::ConnectionStatus::ConnectionFailed;
            emit connectionStatusChanged(_status);
        }
    }
    virtual void close() {
        emit deviceIsClosing();
        disconnect(_dev, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        _dev->close();
        _status = Device::ConnectionStatus::NoConnected;
        emit connectionStatusChanged(_status);
        }
    const Device::ConnectionStatus connectionStatus() {return _status;}
    Device::ConnectionStatus _status;
    QIODevice *_dev; /* QSerialPort, QBuffer, QBluetoothSocket */
public slots:
    void onBytesReceived(qint64 numbytes) {
        QByteArray d = _dev->read(numbytes);
        emit bytesReceived(d.data(), d.size());
    }
    void onReadyRead() {
        _status = Device::ConnectionStatus::Reading;
        emit connectionStatusChanged(_status);
        int numbytes = _dev->bytesAvailable();
        QByteArray d = _dev->read(numbytes);
        emit bytesReceived(d.data(), d.size());
    }
signals:
    void connectionStatusChanged(Brainwave::Device::ConnectionStatus _status);
    void deviceIsClosing();
    void bytesReceived(const char*, int);
};

}
#endif
