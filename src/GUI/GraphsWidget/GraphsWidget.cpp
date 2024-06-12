#include "MainWindow.h"
#include "GraphsWidget.h"
#include "ui_GraphsWidget.h"

GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphsWidget)
{
    ui->setupUi(this);
    MainWindow::mainWindow()->brainwaveInterface()->addListener(this);
}

GraphsWidget::~GraphsWidget()
{
    delete ui;
}

void GraphsWidget::onRaw(float val)
{
    // TODO rewrite raw wave graph
    ui->raw->insertValue((int) (val*2048));
}

void GraphsWidget::onBattery(float val)
{
    
}

void GraphsWidget::onPoorSignal(float val)
{
    int value = 100-(val*100);
    ui->signal->setValue(value);
}

void GraphsWidget::onAttention(float val)
{
    ui->attention->setValue((int)(val*100));
}

void GraphsWidget::onMeditation(float val)
{
    ui->meditation->setValue((int)(val*100));
}

void GraphsWidget::onEeg(Brainwave::EegBands eeg)
{
    ui->eeg->setValues(&(eeg.delta));
}

void GraphsWidget::onBlinkStrength(float val)
{
    
}

/*
void GraphsWidget::onConnecting(unsigned char val)
{
    
}

void GraphsWidget::onReady(unsigned char val)
{
    
}

void GraphsWidget::onError(unsigned char val)
{
    
}
*/
