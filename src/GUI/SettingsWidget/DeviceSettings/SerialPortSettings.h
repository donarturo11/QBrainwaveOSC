#ifndef SERIALPORTSETTINGS_H
#define SERIALPORTSETTINGS_H

#include <QWidget>
#include <QList>
#include <QSerialPortInfo>
#include "DeviceSettings.h"

class SerialPortSettings : public DeviceSettings
{
    Q_OBJECT
    
public:
    SerialPortSettings(QWidget *parent = nullptr);
    ~SerialPortSettings();
    static DeviceSettings* create(QWidget *w);
    QStringList getDevicesList() const;
    QList<qint32> getBaudrates() const override;
    qint32 getBaudrate() const { return _baudrate; }
public slots:
    void setBaudrate(qint32 b) {
        _baudrate = b;
        emit parameterChanged("baudrate", _baudrate);
    }
private:
    void refreshBauds();
protected:
    QList<qint32> _bauds;
    qint32 _baudrate;
};

#endif // DEVICECONFIGURATION_H
