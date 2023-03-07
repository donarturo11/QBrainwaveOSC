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

private:
    Ui::DeviceConfiguration *ui;
};

#endif // DEVICECONFIGURATION_H
