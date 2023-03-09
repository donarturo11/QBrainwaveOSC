#ifndef RFCOMMMONITOR_H
#define RFCOMMMONITOR_H

#include <QWidget>

namespace Ui {
class RfCommMonitor;
}

class RfCommMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit RfCommMonitor(QWidget *parent = nullptr);
    ~RfCommMonitor();
private:
    Ui::RfCommMonitor *ui;
};

#endif // DEVICECONFIGURATION_H
