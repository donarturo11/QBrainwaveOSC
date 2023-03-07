#include "DeviceConfiguration.h"
#include "ui_DeviceConfiguration.h"

DeviceConfiguration::DeviceConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceConfiguration)
{
    ui->setupUi(this);
}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}
