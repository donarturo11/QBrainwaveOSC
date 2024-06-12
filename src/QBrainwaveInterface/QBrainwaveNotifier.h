#ifndef QBRAINWAVE_NOTIFIER_H
#define QBRAINWAVE_NOTIFIER_H
#include <QObject>
#include <QtCore>
#include "DataHandler.h"
#include "EegBands.h"

namespace Brainwave {
class QBrainwaveNotifier : public QObject, public Brainwave::DataHandler
{
    Q_OBJECT
public:
    explicit QBrainwaveNotifier(QObject *parent = nullptr);
    ~QBrainwaveNotifier();
    void addListener(QObject*);
    void removeListener(QObject*);
signals:
    void onRaw(float);
    void onEeg(Brainwave::EegBands);
    void onAttention(float);
    void onMeditation(float);
    void onBlinkStrength(float);
    void onPoorSignal(float);
    void onBattery(float);
/*
signals:
    void notifyRaw(float);
    void notifyEeg(EegBands);
    void notifyAttention(float);
    void notifyMeditation(float);
    void notifyBlinkStrength(float);
    void notifyPoorSignal(float);
    void notifyBattery(float);
*/
};
}
#endif
