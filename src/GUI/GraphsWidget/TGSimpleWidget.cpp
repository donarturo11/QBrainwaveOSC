#include "TGSimpleWidget.h"
#include <QMargins>

int TGSimpleWidget::defaultMax=100;

TGSimpleWidget::TGSimpleWidget(QWidget *parent) 
: TGWidget(parent)
{
    _series = new QHorizontalBarSeries();
    _set = new QBarSet("");
    _maxValue = defaultMax;
    init();
}

TGSimpleWidget::~TGSimpleWidget()
{
    delete _set;
}

void TGSimpleWidget::setValue(int val)
{
    double value = ((double)val/(double)_maxValue)*100;
    _set->replace(0, value);
    series()->append(_set);
}

void TGSimpleWidget::setupAxes()
{
    setupDefaultAxes();
    _axisX->setRange(0,100);
    series()->setBarWidth(1);
}

void TGSimpleWidget::setupFonts()
{
    QFont labelsFont;
    labelsFont.setPixelSize(8);
    _axisX->setLabelsFont(labelsFont);
}

void TGSimpleWidget::initValues()
{
    *_set << 0;
    series()->append(_set);
}

void TGSimpleWidget::setupGui()
{
    _label->setGeometry(0, 0, 100, 40);
    _chartview->setGeometry(100, 0, 500, 50);
    _chart->setMargins(QMargins(0, 0 , 10, 0));
}