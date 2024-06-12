#ifndef DUMMYDEVICESETTINGS_H
#define DUMMYDEVICESETTINGS_H
#include <QWidget>
#include "DeviceSettings.h"


class DummyDeviceSettings : public DeviceSettings
{
    Q_OBJECT
public:
    DummyDeviceSettings(QWidget *parent = nullptr);
    ~DummyDeviceSettings();
    static DeviceSettings* create(QWidget *w);
    QStringList getDevicesList() const;
private:

};
#endif
