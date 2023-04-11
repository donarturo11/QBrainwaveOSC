#ifndef RFCOMMMONITOR_H
#define RFCOMMMONITOR_H

#include <QWidget>
#include <QTextCursor>
#include "ThinkGear.h"
#include "MainWindow.h"
//#include "BluetoothManager.h"
//#include <QBluetoothSocket>
namespace Ui {
class SerialPortMonitor;
}

class SerialPortMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortMonitor(QWidget *parent = nullptr);
    ~SerialPortMonitor();
    void initCursor();
public slots:
    void onDataReceived(QByteArray data);
private:
    Ui::SerialPortMonitor *ui;
    ThinkGear *tg;
    QTextCursor *status_cursor;
};

#endif // DEVICECONFIGURATION_H
