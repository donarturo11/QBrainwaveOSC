#include "QThinkGearDataHandler.h"

int QThinkGearDataHandler::dataCount=0;

void QThinkGearDataHandle( unsigned char extendedCodeLevel,
                            unsigned char code,
                            unsigned char numBytes,
                            const unsigned char *value,
                            void *customData )
{
    auto handler = reinterpret_cast<QThinkGearDataHandler*>(customData);
    handler->pushData(TGData(code, numBytes, value));
}                    

QThinkGearDataHandler::QThinkGearDataHandler(QObject *parent)
: QObject(parent)
{
    
}

void QThinkGearDataHandler::addListener(QObject *listener)
{
    connect(this, SIGNAL(onRaw(short)), listener, SLOT(onThinkGearRaw(short)));
    connect(this, SIGNAL(onBattery(unsigned char)), listener, SLOT(onThinkGearBattery(unsigned char)));
    connect(this, SIGNAL(onPoorSignal(unsigned char)), listener, SLOT(onThinkGearPoorSignal(unsigned char)));
    connect(this, SIGNAL(onAttention(unsigned char)), listener, SLOT(onThinkGearAttention(unsigned char)));
    connect(this, SIGNAL(onMeditation(unsigned char)), listener, SLOT(onThinkGearMeditation(unsigned char)));
    connect(this, SIGNAL(onEeg(EegValues)), listener, SLOT(onThinkGearEeg(EegValues)));
    connect(this, SIGNAL(onConnecting(unsigned char)), listener, SLOT(onThinkGearConnecting(unsigned char)));
    connect(this, SIGNAL(onReady(unsigned char)), listener, SLOT(onThinkGearReady(unsigned char)));
    connect(this, SIGNAL(onError(unsigned char)), listener, SLOT(onThinkGearError(unsigned char)));
    connect(this, SIGNAL(onBlinkStrength(unsigned char)), listener, SLOT(onThinkGearBlinkStrength(unsigned char)));
}

void QThinkGearDataHandler::removeListener(QObject *listener)
{
    
    disconnect(this, SIGNAL(onRaw(short)), listener, SLOT(onThinkGearRaw(short)));
    disconnect(this, SIGNAL(onBattery(unsigned char)), listener, SLOT(onThinkGearBattery(unsigned char)));
    disconnect(this, SIGNAL(onPoorSignal(unsigned char)), listener, SLOT(onThinkGearPoorSignal(unsigned char)));
    disconnect(this, SIGNAL(onAttention(unsigned char)), listener, SLOT(onThinkGearAttention(unsigned char)));
    disconnect(this, SIGNAL(onMeditation(unsigned char)), listener, SLOT(onThinkGearMeditation(unsigned char)));
    disconnect(this, SIGNAL(onEeg(EegValues)), listener, SLOT(onThinkGearEeg(EegValues)));
    disconnect(this, SIGNAL(onConnecting(unsigned char)), listener, SLOT(onThinkGearConnecting(unsigned char)));
    disconnect(this, SIGNAL(onReady(unsigned char)), listener, SLOT(onThinkGearReady(unsigned char)));
    disconnect(this, SIGNAL(onError(unsigned char)), listener, SLOT(onThinkGearError(unsigned char)));
    disconnect(this, SIGNAL(onBlinkStrength(unsigned char)), listener, SLOT(onThinkGearBlinkStrength(unsigned char)));    
     
}

QThinkGearDataHandler::~QThinkGearDataHandler()
{
    
}

void QThinkGearDataHandler::pushData(TGData val)
{
    switch (val.code()) {
        case(ParserCodes::PoorSignal): emit onPoorSignal(val.toUChar()); break;
        case(ParserCodes::Attention): emit onAttention(val.toUChar()); break;
        case(ParserCodes::Meditation): emit onMeditation(val.toUChar()); break;
        case(ParserCodes::RawSignal): emit onRaw(val.toShort()); break;
        case(ParserCodes::Battery): emit onBattery(val.toUChar()); break;
        case(ParserCodes::AsicEegPowerInt): receiveEeg(val); break;
        default: qDebug() << "undefined code: " << val.code();
    }
}

void QThinkGearDataHandler::receiveEeg(TGData val)
{
    auto eeg = val.deserializeArray(8);
    emit onEeg(EegValues(eeg));
}
