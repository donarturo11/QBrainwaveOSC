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

void QThinkGearDataHandler::addListener(QThinkGearListener *listener)
{
    connect(this, &QThinkGearDataHandler::onRaw, listener, &QThinkGearListener::onThinkGearRaw);     
    connect(this, &QThinkGearDataHandler::onBattery, listener, &QThinkGearListener::onThinkGearBattery);
    connect(this, &QThinkGearDataHandler::onPoorSignal, listener, &QThinkGearListener::onThinkGearPoorSignal);
    connect(this, &QThinkGearDataHandler::onAttention, listener, &QThinkGearListener::onThinkGearAttention);
    connect(this, &QThinkGearDataHandler::onMeditation, listener, &QThinkGearListener::onThinkGearMeditation);
    connect(this, &QThinkGearDataHandler::onEeg, listener, &QThinkGearListener::onThinkGearEeg);
    connect(this, &QThinkGearDataHandler::onConnecting, listener, &QThinkGearListener::onThinkGearConnecting);
    connect(this, &QThinkGearDataHandler::onReady, listener, &QThinkGearListener::onThinkGearReady);
    connect(this, &QThinkGearDataHandler::onError, listener, &QThinkGearListener::onThinkGearError);
    connect(this, &QThinkGearDataHandler::onBlinkStrength, listener, &QThinkGearListener::onThinkGearBlinkStrength);
}

void QThinkGearDataHandler::removeListener(QThinkGearListener *listener)
{
    disconnect(this, &QThinkGearDataHandler::onRaw, listener, &QThinkGearListener::onThinkGearRaw);     
    disconnect(this, &QThinkGearDataHandler::onBattery, listener, &QThinkGearListener::onThinkGearBattery);
    disconnect(this, &QThinkGearDataHandler::onPoorSignal, listener, &QThinkGearListener::onThinkGearPoorSignal);
    disconnect(this, &QThinkGearDataHandler::onAttention, listener, &QThinkGearListener::onThinkGearAttention);
    disconnect(this, &QThinkGearDataHandler::onMeditation, listener, &QThinkGearListener::onThinkGearMeditation);
    disconnect(this, &QThinkGearDataHandler::onEeg, listener, &QThinkGearListener::onThinkGearEeg);
    disconnect(this, &QThinkGearDataHandler::onConnecting, listener, &QThinkGearListener::onThinkGearConnecting);
    disconnect(this, &QThinkGearDataHandler::onReady, listener, &QThinkGearListener::onThinkGearReady);
    disconnect(this, &QThinkGearDataHandler::onError, listener, &QThinkGearListener::onThinkGearError);
    disconnect(this, &QThinkGearDataHandler::onBlinkStrength, listener, &QThinkGearListener::onThinkGearBlinkStrength);    
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
