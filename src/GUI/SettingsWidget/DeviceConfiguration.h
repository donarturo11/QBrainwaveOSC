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
    void chooseBaudrate(int id);
    void connectDevice() { tg->open(); }
    void disconnectDevice() { tg->close(); }
    void refresh();
signals:
    void statusNotify(int status);
private:
    Ui::DeviceConfiguration *ui;
    void initBaudRates();
protected:
    Status status;
    QThinkGear *tg;
};

#endif // DEVICECONFIGURATION_H
