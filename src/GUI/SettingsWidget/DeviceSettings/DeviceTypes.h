#ifndef DEVICETYPES_H
#define DEVICETYPES_H
#include <QString>
#include <QVector>
struct DeviceType
{
    QString name;
    QString displayedName;
};

struct SerialDeviceType : DeviceType
{
    QVector<qint32> supportedBaudrates;
};

#endif // DEVICETYPES_H