#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include "GraphsWidget.h"
#include "QThinkGear.h"
#include "TGSimpleWidget.h"
#include "TGWaveWidget.h"
#include "TGEegWidget.h"
/*
namespace Ui {
class GraphsWidget;
}
*/
class GraphsWidget : public QWidget
{
    Q_OBJECT

public:
    GraphsWidget(QWidget *parent = nullptr);
    ~GraphsWidget();
public slots:
    void onThinkGearRaw(short val);
    void onThinkGearBattery(unsigned char val);
    void onThinkGearPoorSignal(unsigned char val);
    void onThinkGearAttention(unsigned char val);
    void onThinkGearMeditation(unsigned char val);
    void onThinkGearEeg(EegValues val);
    void onThinkGearConnecting(unsigned char val);
    void onThinkGearReady(unsigned char val);
    void onThinkGearError(unsigned char val);
    void onThinkGearBlinkStrength(unsigned char val);
private:
    QBoxLayout *_layout;
    TGSimpleWidget *_signal;
    TGSimpleWidget *_attention;
    TGSimpleWidget *_meditation;
    TGEegWidget *_eeggraph;
    TGWaveWidget *_rawgraph;
    QThinkGear *_tg;

};

#endif // MONITORWIDGET_H
