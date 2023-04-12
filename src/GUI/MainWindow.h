#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QThinkGear.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* mainWindow() { return mainwindow; }
    QThinkGear* thinkGear() { return tg; }
    void onDebugReceived(QString msg);
signals:
    void debugReceived(QString msg);
private:
    Ui::MainWindow *ui;
    QThinkGear *tg;
    static MainWindow *mainwindow;

};
#endif // MAINWINDOW_H
