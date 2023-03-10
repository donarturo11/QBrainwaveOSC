#ifndef RFCOMMLISTENER_H
#define RFCOMMLISTENER_H
#include <QObject>
#include <QtCore>
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
    void connect(QString address);
    void disconnect();

public slots:
    void onConnectionRequest(QString address);
    void onDisconnectionRequest();
signals:

protected:
    QBluetoothAddress deviceAddress;
    QBluetoothUuid bt_uuid;
    QBluetoothServer *rfcommServer;
    QBluetoothSocket *socket;
    QBluetoothServiceInfo *service;
    ConnectionStatus status;
};

#endif // RFCOMMLISTENER_H
