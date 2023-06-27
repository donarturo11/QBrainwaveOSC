#ifndef OSCCONFIGURATION_H
#define OSCCONFIGURATION_H

#include <QWidget>
#include "OSCSender.h"

namespace Ui {
class OSCConfiguration;
}

class OSCConfiguration : public QWidget
{
    Q_OBJECT
    
public:
    explicit OSCConfiguration(QWidget *parent = nullptr);
    ~OSCConfiguration();
public slots:
    void onAddressChanged(QString address);
    void onEditingFinished();
    void onPortChanged(int port);
    void onOscOptionChanged(int state);
    void onOscEnabledStateChanged(int state);
private:
    void updateFlags();
protected:
    Ui::OSCConfiguration *ui;
    OSCSender *osc;
};

#endif // OSCCONFIGURATION_H
