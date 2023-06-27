#include "MainWindow.h"
#include "GraphsWidget.h"
#include "ui_GraphsWidget.h"


GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    MainWindow::mainWindow()->thinkGear()->addListener(this);
    _signal = new TGSimpleWidget("Signal", this);
    _signal->setMax(200);
    _attention = new TGSimpleWidget("Attention", this);
    _meditation = new TGSimpleWidget("Meditation", this);
    _eeggraph = new TGEegWidget("Eeg\nvalues", this);
    _rawgraph = new TGWaveWidget("Raw wave: ", this);

    _signal->setGeometry(0,0,750,30);
    _attention->setGeometry(0,30,750,30);
    _meditation->setGeometry(0,60,750,30);
    _eeggraph->setGeometry(0,90,750,180);
    _rawgraph->setGeometry(0,270,750,180);
}

GraphsWidget::~GraphsWidget()
{
    delete _signal;
    delete _attention;
    delete _meditation;
    delete _eeggraph;
    delete _rawgraph;
    delete _layout;
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
    int value = 200-val;
    _signal->setValue(value);
}

void GraphsWidget::onThinkGearAttention(unsigned char val)
{
    _attention->setValue(val);
}

void GraphsWidget::onThinkGearMeditation(unsigned char val)
{
    _meditation->setValue(val);
}

void GraphsWidget::onThinkGearEeg(EegValues val)
{
    _eeggraph->setValues(val);
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
