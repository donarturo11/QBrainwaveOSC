#ifndef DEVICESETTINGSWIDGET_H
#define DEVICESETTINGSWIDGET_H
#include <QWidget>
#include "DeviceSettings.h"

namespace Ui {
class DeviceSettingsWidget;
}

class DeviceSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    DeviceSettingsWidget(QWidget *parent = nullptr);
    ~DeviceSettingsWidget();
    void init();
public slots:
    void refresh();
    void refreshDeviceCombobox();
    void refreshTypeCombobox();
    void refreshBaudrateCombobox();
    void choosePort(int id);
    void chooseDevice(int id);
    void chooseType(int id);
    void chooseBaudrate(int id);
    void onRawWaveStateChanged(int state);
    void onParametersQuery();
signals:
    void baudrateChanged(qint32 baudrate);
    void parametersSent(QVariantMap);
private:
    Ui::DeviceSettingsWidget *ui;
    void initPorts();
protected:
    DeviceSettings* _settings;
};

#endif // DEVICESETTINGS_H
