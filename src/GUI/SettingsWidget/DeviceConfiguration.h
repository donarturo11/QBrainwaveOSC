#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#include <QWidget>
#include "QThinkGear.h"

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
    void chooseBaudRate(int id);
    void chooseType(int id);
    void connectDevice() { tg->open(); }
    void disconnectDevice() { tg->close(); }
    void setupDeviceTypes();
    void refresh();
public slots:
    void onThinkGearStatusChanged(ThinkGearStatus status);
private:
    Ui::DeviceConfiguration *ui;
    void setupBaudRates();
protected:
    Status status;
    QThinkGear *tg;
};

#endif // DEVICECONFIGURATION_H
