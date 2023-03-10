#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    connect(ui->deviceconfiguration, SIGNAL(connectionRequest(QString)), this, SLOT(onConnectionRequest(QString)));
    connect(ui->deviceconfiguration, SIGNAL(disconnectionRequest()), this, SLOT(onDisconnectionRequest()));
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::onConnectionRequest(QString address)
{
    emit connectionRequest(address);
}

void SettingsWidget::onDisconnectionRequest()
{
    emit disconnectionRequest();
}
