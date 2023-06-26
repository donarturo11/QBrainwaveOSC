#ifndef TGWAVE_WIDGET_H
#define TGWAVE_WIDGET_H
#include "TGWidget.h"
#include <QList>
#include <QLineSeries>
#include <QSpinBox>
#include <QLabel>

#define MAXRAWVALUE 2048.0000
#define SAMPLERATE 512.0000

class TGWaveWidget : public TGWidget
{
    Q_OBJECT
public:
    TGWaveWidget(QString label, QWidget *parent = nullptr);
    void insertValue(int val);
    void init();
public slots:
    void setAccuracy(int i) {
        _maxValuesToSave = i;
    }
private:
    void update();
protected:
    QLineSeries *_series;
    QSpinBox *_maxvals_spin;
    QLabel *_maxvals_label;
    QList<double> _saved_values;
    static int _maxValuesToSave;
    int _cur_pos;
};

#endif // TGWAVE_WIDGET_H
