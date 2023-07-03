#include "TGWaveWidget.h"
#include <QPointF>

int TGWaveWidget::_maxValuesToSave = 12;
double TGWaveWidget::_maxGraphWidth = 8;

TGWaveWidget::TGWaveWidget(QWidget *parent) 
: TGWidget(parent)
{
    _cur_pos = 0;
    _series = new QSplineSeries;
    init();
}

TGWaveWidget::~TGWaveWidget()
{}

void TGWaveWidget::setupAxes()
{
    setupDefaultAxes();
    _axisX->setMax(_maxGraphWidth);
    _axisX->setMin(0.0);
    _axisY->setMax(1.0);
    _axisY->setMin(-1.0);
}

void TGWaveWidget::setupGui()
{
    _label->setGeometry(0, 10, 100, 20);
    _chartview->setGeometry(100,0,500,180);
    _axisX->hide();
    _axisY->hide();
}

void TGWaveWidget::initValues()
{
    while (_cur_pos/SAMPLERATE < _maxGraphWidth) {
        insertValue(0);
    }
}

void TGWaveWidget::insertValue(int val)
{
    double y = val/MAXRAWVALUE;
    double x = (double) _cur_pos / SAMPLERATE;
    _saved_values.push_back(y);
    while(_saved_values.size() > _maxValuesToSave)
        _saved_values.pop_front();
    if ((_cur_pos % _maxValuesToSave) == 0)
        update();
    _cur_pos++;
}

void TGWaveWidget::update()
{
    if (_cur_pos<_maxValuesToSave) return;
    QList<QPointF> new_serie;
    int idx=_cur_pos;
    double sum = 0;
    double average = 0;
    double peak = 0;
    for (auto v = _saved_values.begin(); v != _saved_values.end(); v++) {
        if (std::abs(*v) > std::abs(peak)) {
            peak = *v;
        }
        idx++;
    }
    //average = sum / _maxValuesToSave;
    series()->append(QPointF(_cur_pos/SAMPLERATE, peak));

    double min = ((_cur_pos - _maxValuesToSave)/SAMPLERATE) - _maxGraphWidth;
    double max = min + _maxGraphWidth;

    _axisX->setMin(min);
    _axisX->setMax(max);
}
