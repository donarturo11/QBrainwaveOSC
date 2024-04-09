#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QBrainwaveInterface.h"
#include "OSCSender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class OSCSender;
class QBrainwaveInterface;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* mainWindow() { return mainwindow; }
    QBrainwaveInterface* brainwaveInterface() { return _interface; }
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
    QBrainwaveInterface *_interface;
    OSCSender *osc;
    static MainWindow *mainwindow;
    QString _additionalMsg;
};
#endif // MAINWINDOW_H
