#ifndef DEVICESETTINGS_H
#define DEVICESETTINGS_H
#include <QtCore>
#include <QWidget>
#include <QList>
#include <QMap>
#include <QVariant>
#include "DeviceTypes.h"
class DeviceSettings : public QObject
{
    Q_OBJECT
public:
    DeviceSettings(QWidget *parent = nullptr){
        _type = nullptr;
        connect(this, &DeviceSettings::parameterChanged, this, &DeviceSettings::onParameterChanged);
    }
    virtual ~DeviceSettings(){}
    static DeviceSettings* create(QWidget *w) {return nullptr;}
    virtual QStringList getDevicesList() const = 0;
    QMap<QString,QString> getDeviceTypes() const {
        QMap<QString,QString> types;
        for (auto t : _types) {
            types[t.name] = t.displayedName;
        }
        return types;
    }
    QVariantMap getParameters() const { return QVariantMap(_parameters); }
    virtual QList<qint32> getBaudrates() const { return QList<qint32>(); }
    void setPortname(QString name) {
        _portname = name;
        emit parameterChanged("portname", _portname);
    }
    void chooseType(QString typestr) {
        for (auto t : _types) {
            if (t.name == typestr) {
                _type = &t;
                emit parameterChanged("type", _type->name);
                emit typeChanged();
                return;
            }
        }
    }
signals:
    void parameterChanged(QString key, QVariant value);
    void typeChanged();
    void baudrateListChanged();
private slots:
    void onParameterChanged(QString key, QVariant value) {
        _parameters[key] = value;
    }
protected:
    DeviceType *_type;
    QList<DeviceType> _types;
    QString _portname;
    QMap<QString,QVariant> _parameters;
};

#endif // DEVICESETTINGS_H
