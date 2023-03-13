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
    void start();
    void stop();
signals:
    void devicesDetected();
    void finished();
    void deviceDiscovered(const QBluetoothDeviceInfo &dev);
public slots:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onDeviceDiscoveryFinished();
private:
    void search();
    void clear();
protected:
    QBluetoothDeviceDiscoveryAgent* bt_agent;
    QList<QBluetoothDeviceInfo> bt_devices;
};

#endif // BLUETOOTHDISCOVERY_H
