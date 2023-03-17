#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#include <QWidget>
#include "DeviceDiscovery.h"
#include "BluetoothManager.h"

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
    void chooseDevice(int id);
    void chooseBaudrate(int id);
    void onDeviceDiscovered(const QBluetoothDeviceInfo &dev);
signals:
    void statusNotify(int status);
private:
    Ui::DeviceConfiguration *ui;
protected:
    Status status;
    BluetoothManager *bt_manager;
};

#endif // DEVICECONFIGURATION_H
