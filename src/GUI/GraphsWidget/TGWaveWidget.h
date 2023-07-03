#ifndef TGWAVE_WIDGET_H
#define TGWAVE_WIDGET_H
#include "TGWidget.h"
#include <QList>
#include <QSplineSeries>

#define MAXRAWVALUE 2048.0000
#define SAMPLERATE 512.0000

class TGWaveWidget : public TGWidget
{
    Q_OBJECT
public:
    TGWaveWidget(QWidget *parent = nullptr);
    ~TGWaveWidget();
    void insertValue(int val);
    QSplineSeries* series() { return reinterpret_cast<QSplineSeries*>(_series); }
private:
    void update();
    void setupAxes();
    void setupGui();
    void initValues();
protected:
    QList<double> _saved_values;
    static int _maxValuesToSave;
    static double _maxGraphWidth;
    int _cur_pos;
};

#endif // TGWAVE_WIDGET_H
