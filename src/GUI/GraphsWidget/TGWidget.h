#ifndef TGWIDGET_H
#define TGWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QAbstractSeries>

class TGWidget : public QWidget
{
    Q_OBJECT
public:
    TGWidget(QString label, QWidget *parent = nullptr) : QWidget(parent)
    {
        _label = new QLabel(label, this);
        _chart = new QChart;
        _chart->legend()->hide();
        _chartview = new QChartView(_chart, this);
        _chartview->show();
        _label->setGeometry(0, 0, 100, 40);
        _chartview->setGeometry(100,0,500,100);
    }
    virtual ~TGWidget() {
        delete _chart;
        delete _chartview;
        delete _label;
    }
    virtual void init(){}
protected:
    QLabel *_label;
    QChartView *_chartview;
    QChart *_chart;
    QAbstractSeries *_series;
};


#endif // TGWIDGET_H
