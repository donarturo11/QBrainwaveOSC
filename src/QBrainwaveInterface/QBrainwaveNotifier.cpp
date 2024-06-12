#include "QBrainwaveNotifier.h"
namespace Brainwave {

QBrainwaveNotifier::QBrainwaveNotifier(QObject *parent) : QObject(parent)
{}

QBrainwaveNotifier::~QBrainwaveNotifier()
{}

void QBrainwaveNotifier::addListener(QObject *listener)
{
    connect(this, SIGNAL(onBattery(float)), listener, SLOT(onBattery(float)));
    connect(this, SIGNAL(onRaw(float)), listener, SLOT(onRaw(float)));
    connect(this, SIGNAL(onPoorSignal(float)), listener, SLOT(onPoorSignal(float)));
    connect(this, SIGNAL(onAttention(float)), listener, SLOT(onAttention(float)));
    connect(this, SIGNAL(onMeditation(float)), listener, SLOT(onMeditation(float)));
    connect(this, SIGNAL(onEeg(Brainwave::EegBands)), listener, SLOT(onEeg(Brainwave::EegBands)));
    connect(this, SIGNAL(onBlinkStrength(float)), listener, SLOT(onBlinkStrength(float)));
    /*
    connect(this, SIGNAL(onConnecting(unsigned char)), listener, SLOT(onThinkGearConnecting(unsigned char)));
    connect(this, SIGNAL(onReady(unsigned char)), listener, SLOT(onThinkGearReady(unsigned char)));
    connect(this, SIGNAL(onError(unsigned char)), listener, SLOT(onThinkGearError(unsigned char)));
    */
}

void QBrainwaveNotifier::removeListener(QObject *listener)
{
    disconnect(this, SIGNAL(onBattery(float)), listener, SLOT(onBattery(float)));
    disconnect(this, SIGNAL(onRaw(float)), listener, SLOT(onRaw(float)));
    disconnect(this, SIGNAL(onPoorSignal(float)), listener, SLOT(onPoorSignal(float)));
    disconnect(this, SIGNAL(onAttention(float)), listener, SLOT(onAttention(float)));
    disconnect(this, SIGNAL(onMeditation(float)), listener, SLOT(onMeditation(float)));
    disconnect(this, SIGNAL(onEeg(Brainwave::EegBands)), listener, SLOT(onEeg(Brainwave::EegBands)));
    disconnect(this, SIGNAL(onBlinkStrength(float)), listener, SLOT(onBlinkStrength(float)));
    /*
    disconnect(this, SIGNAL(onConnecting(unsigned char)), listener, SLOT(onThinkGearConnecting(unsigned char)));
    disconnect(this, SIGNAL(onReady(unsigned char)), listener, SLOT(onThinkGearReady(unsigned char)));
    disconnect(this, SIGNAL(onError(unsigned char)), listener, SLOT(onThinkGearError(unsigned char)));
    */
}

}
