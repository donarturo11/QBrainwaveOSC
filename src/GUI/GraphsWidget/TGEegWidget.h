#ifndef TGEEG_WIDGET_H
#define TGEEG_WIDGET_H
#include "TGWidget.h"
#include "EegValues.h"
#include "TGValues.h"
#include <QBarSeries>
#include <QBarSet>
#include <QStringList>
#include <QValueAxis>
#include <QBarCategoryAxis>

class TGEegWidget : public TGWidget
{
    Q_OBJECT
public:
    TGEegWidget(QString label, QWidget *parent = nullptr);
    ~TGEegWidget();
    void init();
    void setValues(EegValues vals);
    QBarSeries* series() { return reinterpret_cast<QBarSeries*>(_series); }
private:
    void initAxes();
    void initValues();
    void setupLabels();
    void setupFonts();
protected:
    QBarSet* _eegValues;
    QValueAxis *_axisY;
    QBarCategoryAxis *_axisX;
    
};

#endif // TGEEG_WIDGET_H
