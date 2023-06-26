#include "TGWaveWidget.h"
#include <QValueAxis>

TGWaveWidget::TGWaveWidget(QString label, QWidget *parent) 
: TGWidget(label, parent)
{
    _xpos = 0.000;
    _offset = 0;
    _series = new QLineSeries;
    init();
}

void TGWaveWidget::init()
{
    _label->setGeometry(0, 30, 100, 20);
    _chartview->setGeometry(120,0,400,150);
    _chart->addSeries(_series);
    _chart->createDefaultAxes();
    _chart->axes()[0]->setMax(8.0);
    _chart->axes()[0]->setMin(0.0);
    _chart->axes()[0]->hide();
    _chart->axes()[1]->setMax(1.0);
    _chart->axes()[1]->setMin(-1.0);
    _chart->axes()[1]->hide();
    
    _series->setColor(0x00FF00);
    while (_xpos <= 8.0) {
        _series->append(_xpos, 0);
        _xpos += 0.02;
    }
}

void TGWaveWidget::insertValue(int val)
{
    double y = val/MAXRAWVALUE;
    double x = _xpos;
    _series->replace(_offset, x, y);
    _xpos += 0.02;
    _offset++;
    if (_xpos >= 8.0) {
        _xpos = 0;
        _offset = 0;
    }
}
