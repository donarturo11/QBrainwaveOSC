#include "MainWindow.h"
#include "ui_MainWindow.h"
MainWindow *MainWindow::mainwindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tg(new QThinkGear(this))
    , ui(new Ui::MainWindow)
{
    MainWindow::mainwindow = this;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tg;
}

 void MainWindow::onDebugReceived(QString msg)
{
    //emit debugReceived(msg);
}