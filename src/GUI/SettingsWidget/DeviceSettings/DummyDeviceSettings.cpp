#include "DummyDeviceSettings.h"

DummyDeviceSettings::DummyDeviceSettings(QWidget *parent) :
    DeviceSettings(parent)
{
    //setDevicesList();
    //init();
    emit parameterChanged("porttype", "dummy");
}

DummyDeviceSettings::~DummyDeviceSettings()
{}

DeviceSettings* DummyDeviceSettings::create(QWidget *w)
{
    return (new DummyDeviceSettings(w));
}
QStringList DummyDeviceSettings::getDevicesList() const
{
    QStringList devs;
    devs << "a";
    devs << "b";
    devs << "c";
    return devs;
}
