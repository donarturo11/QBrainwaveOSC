#ifndef RFCOMMMONITOR_H
#define RFCOMMMONITOR_H

#include <QWidget>
#include <QTextCursor>
#include "BluetoothManager.h"
namespace Ui {
class RfCommMonitor;
}

class RfCommMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit RfCommMonitor(QWidget *parent = nullptr);
    ~RfCommMonitor();
    void initCursor();
public slots:
    void onDataReceived(QByteArray data);
private:
    Ui::RfCommMonitor *ui;
    RfcommListener *listener;
    QTextCursor *status_cursor;
};

#endif // DEVICECONFIGURATION_H
