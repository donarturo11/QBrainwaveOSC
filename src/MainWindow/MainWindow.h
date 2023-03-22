#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "RfcommListener.h"
#include "BluetoothManager.h"

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
    void onDebugReceived(QString msg);
signals:
    void debugReceived(QString msg);
private:
    Ui::MainWindow *ui;
    BluetoothManager *bt_manager;
    static MainWindow *mainwindow;

};
#endif // MAINWINDOW_H
