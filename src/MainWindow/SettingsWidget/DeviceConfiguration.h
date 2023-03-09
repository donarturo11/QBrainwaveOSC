#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#include <QWidget>

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
signals:
    void connectionRequest(QString name);
    void disconnectionRequest();
private:
    Ui::DeviceConfiguration *ui;
protected:
    QStringList devices;

};

#endif // DEVICECONFIGURATION_H
