#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "DeviceSettingsWidget.h"

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
    
signals:
    
private:
    Ui::SettingsWidget *ui;
};



#endif // SETTINGSWIDGET_H
