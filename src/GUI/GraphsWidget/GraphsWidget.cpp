#include "MainWindow.h"
#include "GraphsWidget.h"
#include "ui_GraphsWidget.h"

GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphsWidget)
{
    ui->setupUi(this);
    MainWindow::mainWindow()->thinkGear()->addListener(this);
}

GraphsWidget::~GraphsWidget()
{
    delete ui;
}

void GraphsWidget::onThinkGearRaw(short val)
{
    ui->raw->insertValue((int) val);
}

void GraphsWidget::onThinkGearBattery(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearPoorSignal(unsigned char val)
{
    int value = (200-val)/2;
    ui->signal->setValue(value);
}

void GraphsWidget::onThinkGearAttention(unsigned char val)
{
    ui->attention->setValue(val);
}

void GraphsWidget::onThinkGearMeditation(unsigned char val)
{
    ui->meditation->setValue(val);
}

void GraphsWidget::onThinkGearEeg(EegValues val)
{
    ui->eeg->setValues(val);
}

void GraphsWidget::onThinkGearConnecting(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearReady(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearError(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearBlinkStrength(unsigned char val)
{
    
}
