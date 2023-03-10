#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#include <QWidget>
#include "BluetoothDiscovery.h"

typedef enum { NOT_READY, SEARCHING, READY, RUNNING } Status;

namespace Ui {
class DeviceConfiguration;
}

class DeviceConfiguration : public QWidget
{
    Q_OBJECT
    
public:
    explicit DeviceConfiguration(QWidget *parent = nullptr);
    ~DeviceConfiguration();

public slots:
    void refreshDevices();
    void chooseDevice(int id);
    void chooseBaudrate(int id);
    void connectDevice();
    void disconnectDevice();
    void onDiscoveryFinished();
signals:
    void connectionRequest(QString address);
    void disconnectionRequest();
    void refreshRequest();
    void statusNotify(int status);
private:
    Ui::DeviceConfiguration *ui;
protected:
    QList<QBluetoothDeviceInfo> bt_devices;
    BluetoothDiscovery *bt_discovery;
    Status status;
};

#endif // DEVICECONFIGURATION_H
