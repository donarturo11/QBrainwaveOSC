#include "MainWindow.h"
#include "ui_MainWindow.h"
MainWindow *MainWindow::mainwindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _interface(new QBrainwaveInterface(this))
    , ui(new Ui::MainWindow)
{
    MainWindow::mainwindow = this;
    osc = new OSCSender(this);
    ui->setupUi(this);
    connect(_interface, SIGNAL(statusChanged(BrainwaveInterfaceStatus)), this, SLOT(onBrainwaveInterfaceStatusChanged(BrainwaveInterfaceStatus)));
    updateStatusBar();
    _additionalMsg="";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete osc;
    delete _interface;
}

void MainWindow::onDebugReceived(QString msg)
{
    //emit debugReceived(msg);
}

QStatusBar* MainWindow::statusBar()
{
    return ui->statusBar;
}
void MainWindow::onBrainwaveInterfaceStatusChanged(BrainwaveInterfaceStatus status)
{
    updateStatusBar();
}

void MainWindow::msgToStatusBar(QString msg)
{
    statusBar()->showMessage(msg);
}

void MainWindow::updateStatusBar()
{
    QString msg="";
    if (_interface->opened()) {
        msg="Connection on " + _interface->portName();
        msg+="@" + QString::number(_interface->baudRate());
    } else {
        msg="No connected";
        goto finish;
    }
    msg+=" | Parser status: ";
    switch (_interface->status()) {
        case BrainwaveInterfaceStatus::Reading: msg+="Reading..."; break;
        case BrainwaveInterfaceStatus::Idle: msg+="Idle"; break;
        default: msg+="undefined";
    }
    finish:
    msg+=_additionalMsg;
    statusBar()->showMessage(msg);
    _additionalMsg="";
}
