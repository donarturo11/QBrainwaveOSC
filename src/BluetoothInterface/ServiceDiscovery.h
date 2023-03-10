#ifndef SERVICEDISCOVERY_H
#define SERVICEDISCOVERY_H
#include <QObject>
#include <QtCore>
#include <QBluetoothServiceDiscoveryAgent>

class ServiceDiscovery : public QObject
{
    Q_OBJECT
public:
    ServiceDiscovery(const QBluetoothAddress &address, QObject *parent = nullptr);
    ~ServiceDiscovery();
public slots:
    void addService(const QBluetoothServiceInfo &info);
    void onFinished();
private:
    void start();
    void stop();
protected:
    QBluetoothServiceDiscoveryAgent *discoveryAgent;
    QList<QBluetoothDeviceInfo> bt_devices;
};

#endif // SERVICEDISCOVERY_H
