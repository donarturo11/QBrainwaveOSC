#include "QThinkGearDataHandler.h"

int QThinkGearDataHandler::dataCount=0;

void QThinkGearDataHandle( unsigned char extendedCodeLevel,
                            unsigned char code,
                            unsigned char numBytes,
                            const unsigned char *value,
                            void *customData )
{
    auto handler = reinterpret_cast<QThinkGearDataHandler*>(customData);
    handler->pushData(extendedCodeLevel, code, numBytes, value);
}                    

QThinkGearDataHandler::QThinkGearDataHandler(QObject *parent)
: QObject(parent)
{
    
}

QThinkGearDataHandler::~QThinkGearDataHandler()
{
    
}

void QThinkGearDataHandler::pushData(unsigned char extendedCodeLevel,
                                     unsigned char code,
                                     unsigned char numBytes,
                                     const unsigned char *value)
{
    QByteArray val((const char*) value, numBytes);
    int val_s; 
    QDataStream((const char*) value) >> val_s;
    
    qDebug() << "Push data [" << dataCount << "]\t"
             << "Code: " << Qt::hex << code << "\t"
             << "Value: " << val_s ;
    qDebug() << "ByteArray: " << val.toHex();
    dataCount++;
    
}
