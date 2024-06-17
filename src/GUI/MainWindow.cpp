#include "MainWindow.h"
#include "ui_MainWindow.h"
MainWindow *MainWindow::mainwindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _brainwave(new Brainwave::QBrainwaveInterface(this))
    , ui(new Ui::MainWindow)
{
    MainWindow::mainwindow = this;
    _osc = new OSCSender(this);
    ui->setupUi(this);
    connect(_brainwave,
            SIGNAL(connectionStatusChanged(Brainwave::Device::ConnectionStatus)),
            this, 
            SLOT(onConnectionStatusChanged(Brainwave::Device::ConnectionStatus))
            );
    msgToStatusBar("QBrainwaveOSC by donarturo11");
}

MainWindow::~MainWindow()
{
    disconnect(_brainwave, 0, 0, 0);
    _brainwave->deleteConnection();
    delete ui;
    delete _osc;
    delete _brainwave;
}

void MainWindow::onDebugReceived(QString msg)
{
    //emit debugReceived(msg);
}

QStatusBar* MainWindow::statusBar()
{
    return ui->statusBar;
}

void MainWindow::onConnectionStatusChanged(Brainwave::Device::ConnectionStatus status)
{
    using Brainwave::Device::ConnectionStatusMessage;
    msgToStatusBar(ConnectionStatusMessage(status).msg());
}

void MainWindow::msgToStatusBar(QString msg)
{
    statusBar()->showMessage(msg);
}
