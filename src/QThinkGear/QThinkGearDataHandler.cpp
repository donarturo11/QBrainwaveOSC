#include "QThinkGearDataHandler.h"

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
    qDebug() << "Push data" << Qt::hex << extendedCodeLevel;
    qDebug() << "ExCode: " << Qt::hex << extendedCodeLevel;
    qDebug() << "Code: " << Qt::hex << code;
    qDebug() << "NumBytes: " << Qt::hex << numBytes;
    qDebug() << "Value: " << Qt::hex << value;
}
