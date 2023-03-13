#ifndef BLUETOOTHDISCOVERY_H
#define BLUETOOTHDISCOVERY_H
#include <QObject>
#include <QtCore>
#include <QBluetoothDeviceDiscoveryAgent>

class DeviceDiscovery : public QObject
{
    Q_OBJECT
public:
    DeviceDiscovery(QObject *parent = nullptr);
    ~DeviceDiscovery();
    void refresh();
    void updateList();
    QList<QBluetoothDeviceInfo> getDevicesList() { return bt_devices; }
signals:
    void devicesDetected();
    void finished();
private:
    void start();
    void stop();
    void search();
    void clear();
protected:
    QBluetoothDeviceDiscoveryAgent* bt_agent;
    QList<QBluetoothDeviceInfo> bt_devices;
};

#endif // BLUETOOTHDISCOVERY_H
