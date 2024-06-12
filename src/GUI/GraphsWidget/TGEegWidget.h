#ifndef TGEEG_WIDGET_H
#define TGEEG_WIDGET_H
#include "TGWidget.h"
#include <QBarSeries>
#include <QBarSet>
#include <QStringList>
#include <QValueAxis>
#include <QBarCategoryAxis>

class TGEegWidget : public TGWidget
{
    Q_OBJECT
public:
    TGEegWidget(QWidget *parent = nullptr);
    ~TGEegWidget();
    void setValues(float*);
    QBarSeries* series() { return reinterpret_cast<QBarSeries*>(_series); }
private:
    void setupAxes();
    void setupGui();
    void initValues();
    void update() { series()->append(_eegValues); }
    void setupFonts();
    void setupLabels();
protected:
    QBarSet* _eegValues;
};

#endif // TGEEG_WIDGET_H
