#include "OSCConfiguration.h"
#include "ui_OSCConfiguration.h"
#include "MainWindow.h"

OSCConfiguration::OSCConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OSCConfiguration)
{
    ui->setupUi(this);
}

OSCConfiguration::~OSCConfiguration()
{
    delete ui;
}
