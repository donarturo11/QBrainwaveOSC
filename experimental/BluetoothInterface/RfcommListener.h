#ifndef RFCOMMLISTENER_H
#define RFCOMMLISTENER_H
#include <QObject>
#include <QtCore>
#include <QBluetoothLocalDevice>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothUuid>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>

typedef enum {ERROR = -1, CONNECTED, DISCONNECTED} ConnectionStatus;
class RfcommListener : public QObject
{
    Q_OBJECT
public:
    RfcommListener(QObject *parent = nullptr);
    ~RfcommListener();
    void connectService(QBluetoothServiceInfo& remoteService);
    void disconnectService();

public slots:
    void readData();
    void writeData();
signals:
    void receivedData(QByteArray data);
    void stateChanged(QBluetoothSocket::SocketState state);
protected:
    QBluetoothLocalDevice localDevice;
    QBluetoothAddress remoteAddress;
    QBluetoothUuid bt_uuid;
    QBluetoothServer *rfcommServer;
    QBluetoothSocket *socket;
    QBluetoothServiceInfo *service;
    ConnectionStatus status;
    qint16 port;
    bool running;
};
#endif // RFCOMMLISTENER_H
