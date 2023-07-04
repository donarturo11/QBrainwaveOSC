#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QThinkGear.h"
#include "OSCSender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class OSCSender;
class QThinkGear;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* mainWindow() { return mainwindow; }
    QThinkGear* thinkGear() { return tg; }
    OSCSender* oscSender() { return osc; }
    QStatusBar* statusBar();
    void msgToStatusBar(QString msg);
    void onDebugReceived(QString msg);
    void updateStatusBar();
public slots:
    void onThinkGearStatusChanged(ThinkGearStatus status);
signals:
    void debugReceived(QString msg);
private:
    Ui::MainWindow *ui;
    QThinkGear *tg;
    OSCSender *osc;
    static MainWindow *mainwindow;
    QString _additionalMsg;
};
#endif // MAINWINDOW_H
