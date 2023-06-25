#include "GraphsWidget.h"
#include "ui_GraphsWidget.h"

GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphsWidget)
{
    ui->setupUi(this);
}

GraphsWidget::~GraphsWidget()
{
    delete ui;
}
