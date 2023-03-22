#ifndef DEBUGMONITOR_H
#define DEBUGMONITOR_H
#include <QWidget>
#include <QTextCursor>
#include "MainWindow.h"
namespace Ui {
class DebugMonitor;
}

class DebugMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit DebugMonitor(QWidget *parent = nullptr);
    ~DebugMonitor();
    void initCursor();
public slots:
    void onDebugReceived(QString dbgString);
private:
    Ui::DebugMonitor *ui;
    QTextCursor *status_cursor;
    MainWindow *mainwindow;
};

#endif // DEBUGMONITOR_H
