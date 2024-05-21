#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    connect(ui->connection, SIGNAL(parametersQuery()),
            ui->device_settings, SLOT(onParametersQuery()));
    connect(ui->device_settings, SIGNAL(parametersSent(QVariantMap)),
            ui->connection, SLOT(onParametersReceived(QVariantMap)));
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}



