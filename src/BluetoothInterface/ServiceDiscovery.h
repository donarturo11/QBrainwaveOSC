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
    void updateServicesList();
    QList<QBluetoothServiceInfo> getServicesList() { return detectedServices; }
public slots:
    void addService(const QBluetoothServiceInfo &info);
    void refresh();
    void onFinished();
protected:
    QBluetoothServiceDiscoveryAgent *discoveryAgent;
    QList<QBluetoothServiceInfo> detectedServices;
};

#endif // SERVICEDISCOVERY_H
