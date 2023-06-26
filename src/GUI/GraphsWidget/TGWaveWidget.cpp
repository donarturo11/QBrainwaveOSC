#include "TGWaveWidget.h"
#include <QPointF>

int TGWaveWidget::_maxValuesToSave = 8;

TGWaveWidget::TGWaveWidget(QString label, QWidget *parent) 
: TGWidget(label, parent)
{
    _cur_pos = 0;
    _series = new QLineSeries;
    init();
}

void TGWaveWidget::init()
{
    _label->setGeometry(0, 30, 100, 20);
    _chartview->setGeometry(120,0,400,200);
    _chart->addSeries(_series);
    _chart->createDefaultAxes();
    _chart->axes()[0]->setMax(4.0);
    _chart->axes()[0]->setMin(0.0);
    _chart->axes()[0]->hide();
    _chart->axes()[1]->setMax(1.0);
    _chart->axes()[1]->setMin(-1.0);
    _chart->axes()[1]->hide();

    _maxvals_spin = new QSpinBox(this);
    _maxvals_label = new QLabel("Samples\nper point", this);

    _maxvals_label->setGeometry(0,60,80,40);
    _maxvals_spin->setGeometry(0,100,50,25);
    _maxvals_spin->setRange(2,16);
    _maxvals_spin->setValue(_maxValuesToSave);
    connect(_maxvals_spin, &QSpinBox::valueChanged, this, &TGWaveWidget::setAccuracy);

    _series->setColor(0x00FF00);

    for (int i=0; i<(512*4); i++) {
        insertValue(0);
    }
}

void TGWaveWidget::insertValue(int val)
{
    double y = val/2048.0000f;
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
    for (auto v = _saved_values.begin(); v != _saved_values.end(); v++) {
        sum += *v;
        idx++;
    }
    average = sum / _maxValuesToSave;
    _series->append(QPointF(_cur_pos/SAMPLERATE, average));

    double min = ((_cur_pos - _maxValuesToSave)/SAMPLERATE) - 4;
    double max = min+4;

    _chart->axes()[0]->setMin(min);
    _chart->axes()[0]->setMax(max);
}
