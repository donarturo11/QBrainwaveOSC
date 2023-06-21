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
    void pushData(unsigned char extendedCodeLevel,
                  unsigned char code,
                  unsigned char numBytes,
                  const unsigned char *value);
private:
    void handleEeg(QByteArray d);
};


#endif // QTHINKGEARDATAHANDLER_H
