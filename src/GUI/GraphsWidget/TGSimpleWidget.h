#ifndef TGSIMPLEWIDGET_H
#define TGSIMPLEWIDGET_H
#include "TGWidget.h"
#include <QHorizontalBarSeries>
#include <QBarSet>
#include <QLabel>
#include <QValueAxis>
#include <QBarCategoryAxis>

class TGSimpleWidget : public TGWidget
{
    Q_OBJECT
public:
    TGSimpleWidget(QString label, QWidget *parent = nullptr);
    ~TGSimpleWidget();
    void init();
    void setValue(int val);
    QHorizontalBarSeries* series() { 
        return reinterpret_cast<QHorizontalBarSeries*>(_series);
        }
    void setMax(int v) { _maxValue = v; }
    static int defaultMax;
private:
    void setupAxes();
    void setupGui();
    void setupFonts();
    void initValues();
protected:
    QBarSet *_set;
    int _maxValue;
};

#endif // TGSIMPLEWIDGET_H
