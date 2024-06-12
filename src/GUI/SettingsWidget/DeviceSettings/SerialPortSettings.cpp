#include "SerialPortSettings.h"
#include "MainWindow.h"
#include <iostream>
#include "DeviceTypes.h"
#include "DeviceSettingsWidget.h"

const SerialDeviceType serialTypes[] {
    {"ThinkGearStreamParser", "ThinkGear Stream Parser", {9600, 57600}},
    {"TwoByteRawParser", "2-byte raw wave parser (unsigned 12-bit)", {19200, 38400, 57600}},
};
const QVector<qint32> standardBaudrates( {
    57600, 38400, 19200, 9600
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
    /*
    QVector<qint32> bauds = (_type ?
                            (reinterpret_cast<SerialDeviceType*>(_type)->supportedBaudrates) :
                             standardBaudrates);
    */
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
