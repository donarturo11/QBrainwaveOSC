#include "SerialPortSettings.h"
#include "MainWindow.h"
#include <iostream>
#include "DeviceTypes.h"
#include "DeviceSettingsWidget.h"

#ifndef STANDARD_BAUDS
#define STANDARD_BAUDS { 115200, 57600, 38400, 19200, 9600 }
#endif
#ifndef THINKGEAR_BAUDS
#define THINKGEAR_BAUDS { 57600, 9600 }
#endif

SerialPortSettings::SerialPortSettings(QWidget *parent) :
    DeviceSettings(parent)
{
    for (auto t : deviceTypes) {
        if (t.porttype == "serial") {
            _types.append(t);
        }
    }
    _type = nullptr;
    refreshBauds();
    connect(parent,
            SIGNAL(baudrateChanged(qint32)),
            this,
            SLOT(setBaudrate(qint32)));
    connect(this,
            SIGNAL(baudrateListChanged()),
            parent,
            SLOT(refreshBaudrateCombobox()));

    connect(this,
            &SerialPortSettings::typeChanged,
            this,
            &SerialPortSettings::refreshBauds);
    emit parameterChanged("porttype", "serial");
}

SerialPortSettings::~SerialPortSettings()
{}

DeviceSettings* SerialPortSettings::create(QWidget *w)
{
    return (new SerialPortSettings(w));
}

void SerialPortSettings::refreshBauds()
{
    if (_type) {
        _bauds = (_type->name == "ThinkGearStreamParser")
                                 ? QList<qint32>(THINKGEAR_BAUDS)
                                 : QList<qint32>(STANDARD_BAUDS);
    }
    emit baudrateListChanged();
}

QStringList SerialPortSettings::getDevicesList() const
{
        QStringList devs;
        auto ports = QSerialPortInfo::availablePorts();
        for (auto p : ports ) {
            devs << p.portName();
        }
        devs.sort();
        return devs;        
}

QList<qint32> SerialPortSettings::getBaudrates() const
{
    return _bauds;
}
