#include "MainWindow.h"
#include "GraphsWidget.h"
#include "ui_GraphsWidget.h"


GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    MainWindow::mainWindow()->thinkGear()->addListener(this);
    _rawgraph = new TGWaveWidget("Raw wave: ", this);
    
}

GraphsWidget::~GraphsWidget()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void GraphsWidget::onThinkGearRaw(short val)
{
    _rawgraph->insertValue((int) val);
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
