#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H
#include <QObject>
#include <QtCore>
#include "DeviceDiscovery.h"
#include "ServiceDiscovery.h"
#include "RfcommListener.h"

class BluetoothManager : public QObject
{
    Q_OBJECT
public:
    BluetoothManager(QObject *parent = nullptr);
    ~BluetoothManager();
    void printPtr();
    static const BluetoothManager* bluetoothManager(){ return currentInstance; };
signals:
    void deviceDiscoveryFinished();
public slots:
    /*void connect(QString address);
    void disconnect();
    void startServer();
    void stopServer();
    void discoveryDevices();
    void discoveryServices();*/
private:
    //void setupServer();
protected:
    static BluetoothManager *currentInstance;
    DeviceDiscovery *dev_discovery;
    RfcommListener *bt_listener;
};

#endif // BLUETOOTHMANAGER_H
