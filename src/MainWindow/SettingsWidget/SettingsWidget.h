#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "DeviceConfiguration.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();
public slots:
    void onConnectionRequest(QString name);
    void onDisconnectionRequest();
signals:
    void connectionStatusChanged(int status); //receive from BrainwaveConnection
private:
    Ui::SettingsWidget *ui;

};

#endif // SETTINGSWIDGET_H
