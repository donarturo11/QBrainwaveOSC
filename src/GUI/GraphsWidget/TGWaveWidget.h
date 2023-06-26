#ifndef TGWAVE_WIDGET_H
#define TGWAVE_WIDGET_H
#include "TGWidget.h"
#include <QLineSeries>

#define MAXRAWVALUE 2048.0000

class TGWaveWidget : public TGWidget
{
    Q_OBJECT
public:
    TGWaveWidget(QString label, QWidget *parent = nullptr);
    void insertValue(int val);
    void init();
    double _xpos;
    int _offset;
private:
    QLineSeries *_series;
    
    
};

#endif // TGWAVE_WIDGET_H
