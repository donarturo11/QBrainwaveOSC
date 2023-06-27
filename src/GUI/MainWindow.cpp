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
