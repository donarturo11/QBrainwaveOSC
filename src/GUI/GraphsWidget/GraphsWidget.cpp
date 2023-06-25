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
    
}

void GraphsWidget::onThinkGearBattery(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearPoorSignal(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearAttention(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearMeditation(unsigned char val)
{
    
}

void GraphsWidget::onThinkGearEeg(EegValues val)
{
    
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
