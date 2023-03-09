#include "MonitorWidget.h"
#include "ui_MonitorWidget.h"

MonitorWidget::MonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorWidget)
{
    ui->setupUi(this);
}

MonitorWidget::~MonitorWidget()
{
    delete ui;
}
