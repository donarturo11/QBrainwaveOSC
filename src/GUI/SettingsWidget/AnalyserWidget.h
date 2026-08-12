#ifndef ANALYSERWIDGET_H
#define ANALYSERWIDGET_H
#include <QWidget>
#include <QComboBox>
#include "RawWaveAnalyser.h"

namespace Ui {
class AnalyserWidget;
}

class AnalyserWidget : public QWidget
{
    Q_OBJECT

public:
    AnalyserWidget(QWidget *parent = nullptr);
    ~AnalyserWidget();
    void init();
public slots:
    void refresh();
    void onRawWaveStateChanged(int state);
    void onSamplerateChanged(int);
    void onParametersQuery();
signals:
    void parametersSent(QVariantMap);
private:
    Ui::AnalyserWidget *ui;
    void initSampleratesList();
protected:
    
};

#endif // ANALYSERWIDGET_H
