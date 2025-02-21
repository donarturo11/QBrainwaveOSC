#ifndef DEVICETYPES_H
#define DEVICETYPES_H
#include <QString>
#include <QVector>
struct DeviceType
{
    QString porttype;
    QString name;
    QString displayedName;
};

inline QVector<DeviceType> deviceTypes {
    {"serial", "ThinkGearStreamParser", "ThinkGear Stream Parser"},
    {"serial", "TwoByteRawParser", "2-byte raw wave parser (unsigned 12-bit)"}
};

#endif // DEVICETYPES_H
