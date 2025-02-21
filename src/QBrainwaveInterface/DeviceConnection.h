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
        if (_dev->isOpen()) {
            qDebug() << "Device is already open";
            return;
        }
        #ifdef QT6
            auto open_opt = QIODeviceBase::ReadWrite;
        #else
            auto open_opt = QIODevice::ReadWrite;
        #endif
        setConnectionStatus(Device::ConnectionStatus::Connecting);
        if(_dev->open(open_opt)) {
            connect(_dev, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        setConnectionStatus(Device::ConnectionStatus::Connected);
        } else {
            setConnectionStatus(Device::ConnectionStatus::ConnectionFailed);
        }
    }
    virtual void close() {
        setConnectionStatus(Device::ConnectionStatus::Disconnecting);
        disconnect(_dev, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        _dev->close();
        setConnectionStatus(Device::ConnectionStatus::NoConnected);
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
        setConnectionStatus(Device::ConnectionStatus::Reading);
        int numbytes = _dev->bytesAvailable();
        QByteArray d = _dev->read(numbytes);
        emit bytesReceived(d.data(), d.size());
        //setConnectionStatus(Device::ConnectionStatus::Idle);
    }
signals:
    void connectionStatusChanged(Brainwave::Device::ConnectionStatus);
    void bytesReceived(const char*, int);
private:
    void setConnectionStatus(Brainwave::Device::ConnectionStatus status) {
        _status = status;
        emit connectionStatusChanged(_status);
    }
};

}
#endif
