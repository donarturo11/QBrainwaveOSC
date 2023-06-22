#include "QThinkGearDataHandler.h"
#include "eegValues.h"

int QThinkGearDataHandler::dataCount=0;

void QThinkGearDataHandle( unsigned char extendedCodeLevel,
                            unsigned char code,
                            unsigned char numBytes,
                            const unsigned char *value,
                            void *customData )
{
    auto handler = reinterpret_cast<QThinkGearDataHandler*>(customData);
    TGData val(code, numBytes, value);
    handler->pushData(val);
}                    

QThinkGearDataHandler::QThinkGearDataHandler(QObject *parent)
: QObject(parent)
{
    
}

QThinkGearDataHandler::~QThinkGearDataHandler()
{
    
}

void QThinkGearDataHandler::pushData(TGData val)
{
    
    switch (val.code()) {
        case(ParserCodes::Battery): break;
        case(ParserCodes::AsicEegPowerInt): receiveEeg(val); break;
    }
    
}

void QThinkGearDataHandler::receiveEeg(TGData val)
{
    auto eeg = val.deserializeArray(8);
    EegValues eegVals(eeg);
    /*
    qDebug() << "Eeg values: ";
    auto arr = QByteArray((const char*) val.value(), val.size()).toHex();
    for (int i = 6; i <= 48; i++) {
        arr.insert(i, " ");
        i += 6;
    }
    qDebug() << arr;
    for ( auto v : eegVals.getAllValues() ) {
        qDebug() << "Name: " << v.name();
        qDebug() << "Key: " << v.key();
        qDebug() << "Value: " << Qt::hex << v.value();
    }
   qDebug() << " ";
   */
   // emit onEeg(eeg) 
    
}
