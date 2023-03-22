#include "MainWindow.h"
#include "ui_MainWindow.h"
MainWindow *MainWindow::mainwindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , bt_manager(new BluetoothManager(this))
    , ui(new Ui::MainWindow)
{
    MainWindow::mainwindow = this;
    ui->setupUi(this);
    /*
    connect(ui->settings_widget, SIGNAL(connectionRequest(QString)),
            rfcommListener, SLOT(onConnectionRequest(QString)));
    connect(ui->settings_widget, SIGNAL(disconnectionRequest()),
            rfcommListener, SLOT(onDisconnectionRequest()));
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bt_manager;
}

 void MainWindow::onDebugReceived(QString msg)
{
    fprintf(stderr, "MainWindow::onDebugRecived\n");
    emit debugReceived(msg);
}