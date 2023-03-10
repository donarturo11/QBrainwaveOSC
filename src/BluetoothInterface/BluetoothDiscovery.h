#ifndef BLUETOOTHDISCOVERY_H
#define BLUETOOTHDISCOVERY_H
#include <QObject>
#include <QtCore>
#include <QBluetoothDeviceDiscoveryAgent>

class BluetoothDiscovery : public QObject
{
    Q_OBJECT
public:
    BluetoothDiscovery(QObject *parent = nullptr);
    ~BluetoothDiscovery();
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
