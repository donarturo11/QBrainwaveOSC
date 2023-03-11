#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H
#include <QObject>
#include <QtCore>
#include <memory>
#include "DeviceDiscovery.h"
#include "ServiceDiscovery.h"
#include "RfcommListener.h"

class BluetoothManager : public QObject
{
    Q_OBJECT
public:
    BluetoothManager(QObject *parent = nullptr);
    ~BluetoothManager();
    void setup(QString addressStr);
    void setupDevice(QBluetoothAddress address);
    void setupService();
    void printPtr();
    QList<QBluetoothDeviceInfo> getDevicesList(){ return bt_devices; }
    static BluetoothManager* bluetoothManager(){ return currentInstance; };
signals:
    void deviceDiscoveryFinished();
public slots:
    void updateDevicesList();
    void refreshDevices();
    void connectDevice();
    void disconnectDevice();
private:
    //void setupServer();
    bool rfcommEnabled(const QBluetoothServiceInfo &serviceInfo);
protected:
    static BluetoothManager *currentInstance;
    DeviceDiscovery dev_discovery;
    RfcommListener bt_listener;
    QBluetoothLocalDevice localDevice;
    QBluetoothDeviceInfo currentRemoteDevice;
    QBluetoothServiceInfo currentRemoteService;
    QList<QBluetoothDeviceInfo> bt_devices;
    QList<QBluetoothServiceInfo> bt_services;
};

#endif // BLUETOOTHMANAGER_H
