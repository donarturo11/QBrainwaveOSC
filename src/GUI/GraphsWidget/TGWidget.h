#ifndef TGWIDGET_H
#define TGWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QAbstractSeries>
#include <QValueAxis>
#ifdef QT5
using namespace QtCharts;
#endif
class TGWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString label READ getLabel WRITE setLabel)
public:
    TGWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        _label = new QLabel(this);
        _chart = new QChart;
        _chartview = new QChartView(_chart, this);
        _label->setGeometry(0, 0, 100, 40);
        _chartview->setGeometry(100,0,500,100);
        _chart->legend()->hide();
        _chartview->show();
    }
    virtual ~TGWidget() {
        if (_series)
            delete _series;
        delete _chart;
        delete _chartview;
        delete _label;
    }
    void setLabel(QString l) { _label->setText(l); }
    QString getLabel() { return _label->text(); }
    virtual void init(){
        if (_series)
            _chart->addSeries(_series);
        setupAxes();
        setupGui();
        initValues();
        }
    void setupDefaultAxes(){
        _chart->createDefaultAxes();
        _axisX = reinterpret_cast<QValueAxis*>(_chart->axes()[0]);
        _axisY = reinterpret_cast<QValueAxis*>(_chart->axes()[1]);
        }
private:
    virtual void setupAxes(){}
    virtual void setupGui(){}
    virtual void initValues(){}
protected:
    QLabel *_label;
    QChartView *_chartview;
    QChart *_chart;
    QAbstractSeries *_series;
    QValueAxis *_axisX;
    QValueAxis *_axisY;
};


#endif // TGWIDGET_H
