#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include "GraphsWidget.h"
#include "QThinkGear.h"
#include "QThinkGearListener.h"

namespace Ui {
class GraphsWidget;
}

class GraphsWidget : public QWidget, public QThinkGearListener
{
    Q_OBJECT

public:
    explicit GraphsWidget(QWidget *parent = nullptr);
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
    Ui::GraphsWidget *ui;
    QThinkGear *_tg;

};

#endif // MONITORWIDGET_H
