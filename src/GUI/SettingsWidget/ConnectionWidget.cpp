#include "ConnectionWidget.h"
#include "ui_ConnectionWidget.h"
#include "MainWindow.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWidget),
    _ready(false),
    _brainwave(MainWindow::mainWindow()->brainwaveInterface())
{
    ui->setupUi(this);

    connect(ui->connect_btn, SIGNAL(clicked()),
            this, SLOT(connectDevice()));
    connect(ui->disconnect_btn, SIGNAL(clicked()),
            this, SLOT(disconnectDevice()));
    connect(_brainwave, SIGNAL(connectionStatusChanged(Brainwave::ConnectionStatus)),
            this, SLOT(onConnectionStatusChanged(Brainwave::ConnectionStatus)));
}

ConnectionWidget::~ConnectionWidget()
{
    delete ui;
}

void ConnectionWidget::onConnectionStatusChanged(Brainwave::ConnectionStatus status)
{
    qDebug() << __FUNCTION__ << " not yet implemented";
}

void ConnectionWidget::onParametersReceived(QVariantMap p)
{
    _parameters = p;
    _ready = true;
}

void ConnectionWidget::connectDevice()
{
    emit parametersQuery();
    while (!_ready);
    _brainwave->setupConnection(_parameters);
    _brainwave->open();
}

void ConnectionWidget::disconnectDevice()
{
    _brainwave->close();
    _brainwave->deleteConnection();
    _ready = false;
}
