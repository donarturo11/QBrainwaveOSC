#include "SerialPortSettings.h"
#include "MainWindow.h"
#include <iostream>
#include "DeviceTypes.h"
#include "DeviceSettingsWidget.h"

const DeviceType serialTypes[] {
    {"ThinkGearStreamParser", "ThinkGear Stream Parser"},
    {"TwoByteRawParser", "2-byte raw wave parser (unsigned 12-bit)"}
};
const QVector<qint32> standardBaudrates( {
    115200, 57600, 38400, 19200, 9600
}
);


SerialPortSettings::SerialPortSettings(QWidget *parent) :
    DeviceSettings(parent)
{
    for (auto t : serialTypes) {
        _types.append(t);
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
    _bauds.clear();
    for (auto b : standardBaudrates) {
        _bauds.append(b);
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
