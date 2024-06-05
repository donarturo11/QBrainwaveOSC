#include "QBrainwaveNotifier.h"
namespace Brainwave {

QBrainwaveNotifier::QBrainwaveNotifier(QObject *parent) : QObject(parent)
{
    qDebug() << "QBrainwaveNotifier c-tor";
}

QBrainwaveNotifier::~QBrainwaveNotifier()
{
    qDebug() << "QBrainwaveNotifier d-tor";
}
/*
void QBrainwaveNotifier::onRaw(float value)
{

}

void QBrainwaveNotifier::onEeg(EegBands bands)
{

}

void QBrainwaveNotifier::onAttention(float value)
{

}

void QBrainwaveNotifier::onMeditation(float value)
{

}

void QBrainwaveNotifier::onBlinkStrength(float value)
{

}

void QBrainwaveNotifier::onPoorSignal(float value)
{

}

void QBrainwaveNotifier::onBattery(float value)
{

}
*/
}
