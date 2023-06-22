#ifndef QTHINKGEARDATAHANDLER_H
#define QTHINKGEARDATAHANDLER_H
#include <QObject>
#include <QtCore>
#include "TGData.h"

/**
 *  Data CODE definitions:
 *  (ThinkGearStreamParser.h)
 *
 *  PARSER_CODE_BATTERY            0x01
 *  PARSER_CODE_POOR_QUALITY       0x02
 *  PARSER_CODE_ATTENTION          0x04
 *  PARSER_CODE_MEDITATION         0x05
 *  PARSER_CODE_8BITRAW_SIGNAL     0x06
 *  PARSER_CODE_RAW_MARKER         0x07
 *  PARSER_CODE_RAW_SIGNAL         0x80
 *  PARSER_CODE_EEG_POWERS         0x81
 *  PARSER_CODE_ASIC_EEG_POWER_INT 0x83
 */
typedef enum {
    Battery=0x01,
    PoorSignal,
    HeartRate,
    Attention,
    Meditation,
    Raw8Bit,
    RawMarker,
    RawSignal=0x80,
    EegPowers,
    AsicEegPowerInt=0x83,
    SyncByte=0xAA,
    ExcodeByte=0x55
} ParserCodes;

void QThinkGearDataHandle( unsigned char extendedCodeLevel,
                            unsigned char code,
                            unsigned char numBytes,
                            const unsigned char *value,
                            void *customData );
                            
class QThinkGearDataHandler : public QObject
{
    Q_OBJECT
public:
    QThinkGearDataHandler(QObject *parent = nullptr);
    ~QThinkGearDataHandler();
    static int dataCount;
    void pushData(TGData val);
private:
    void receiveEeg(TGData val);
};


#endif // QTHINKGEARDATAHANDLER_H
