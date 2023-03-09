#include "RfCommMonitor.h"
#include "ui_RfCommMonitor.h"
#include <QList>
RfCommMonitor::RfCommMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RfCommMonitor)
{
    ui->setupUi(this);
}

RfCommMonitor::~RfCommMonitor()
{
    delete ui;
}
