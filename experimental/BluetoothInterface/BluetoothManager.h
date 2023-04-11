#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H
#include <QObject>
#include <QtCore>
#include <QtCore>
#include <memory>
#include "DeviceDiscovery.h"
#include "ServiceDiscovery.h"
#include "RfcommListener.h"

class BluetoothManagerError {};

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
    bool isSetupReady(){ return setupReady; }
    static BluetoothManager* bluetoothManager(){ return currentInstance; };
    RfcommListener* btListener() {return &bt_listener;}
signals:
    void deviceDiscoveryFinished();
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void serviceFound();
    void receivedData(char* data);
public slots:
    void refreshDevices();
    void connectDevice();
    void disconnectDevice();
    void onDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onServiceDiscovered(const QBluetoothServiceInfo &info);
    void onServiceDiscoveryFinished();
    void startDeviceDiscovery();
    void stopDeviceDiscovery();
private:
    bool serialPortEnabled(const QBluetoothServiceInfo &serviceInfo);
    void startServiceDiscovery();
    void stopServiceDiscovery();
protected:
    static BluetoothManager *currentInstance;
    DeviceDiscovery dev_discovery;
    ServiceDiscovery *srv_discovery;
    RfcommListener bt_listener;
    QBluetoothLocalDevice localDevice;
    QBluetoothDeviceInfo currentRemoteDevice;
    QBluetoothServiceInfo currentRemoteService;
    QList<QBluetoothDeviceInfo> bt_devices;
    QList<QBluetoothServiceInfo> bt_services;
    bool setupReady;
    bool serviceDiscovered;
};

#endif // BLUETOOTHMANAGER_H
