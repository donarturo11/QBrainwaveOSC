#include "MainWindow.h"
#include "ui_MainWindow.h"
MainWindow *MainWindow::mainwindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tg(new QThinkGear(this))
    , ui(new Ui::MainWindow)
{
    MainWindow::mainwindow = this;
    osc = new OSCSender(this);
    ui->setupUi(this);
    connect(tg, SIGNAL(statusChanged(ThinkGearStatus)), this, SLOT(onThinkGearStatusChanged(ThinkGearStatus)));
    updateStatusBar();
    _additionalMsg="";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete osc;
    delete tg;
}

void MainWindow::onDebugReceived(QString msg)
{
    //emit debugReceived(msg);
}

QStatusBar* MainWindow::statusBar()
{
    return ui->statusBar;
}
void MainWindow::onThinkGearStatusChanged(ThinkGearStatus status)
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
    if (tg->opened()) {
        msg="Connection on " + tg->portName();
        msg+="@" + QString::number(tg->baudRate());
    } else {
        msg="No connected";
        goto finish;
    }
    msg+=" | Parser status: ";
    switch (tg->status()) {
        case ThinkGearStatus::Reading: msg+="Reading..."; break;
        case ThinkGearStatus::Idle: msg+="Idle"; break;
        default: msg+="undefined";
    }
    finish:
    msg+=_additionalMsg;
    statusBar()->showMessage(msg);
    _additionalMsg="";
}
