#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include "GraphsWidget.h"
#include "EegBands.h"
#include "TGSimpleWidget.h"
#include "TGWaveWidget.h"
#include "TGEegWidget.h"

namespace Ui {
class GraphsWidget;
}

class GraphsWidget : public QWidget
{
    Q_OBJECT

public:
    GraphsWidget(QWidget *parent = nullptr);
    ~GraphsWidget();
public slots:
    void onRaw(float val);
    void onBattery(float val);
    void onPoorSignal(float val);
    void onAttention(float val);
    void onMeditation(float val);
    void onEeg(Brainwave::EegBands eeg);
    void onBlinkStrength(float val);
    /*
    void onThinkGearConnecting(unsigned char val);
    void onThinkGearReady(unsigned char val);
    void onThinkGearError(unsigned char val);
    */
private:
    Ui::GraphsWidget *ui;
};

#endif // MONITORWIDGET_H
