#ifndef QTHINKGEARDATAHANDLER_H
#define QTHINKGEARDATAHANDLER_H
#include <QObject>
#include <QtCore>
#include "TGData.h"
#include "EegValues.h"

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
class QThinkGearListener;                            
class QThinkGearDataHandler : public QObject
{
    Q_OBJECT
public:
    QThinkGearDataHandler(QObject *parent = nullptr);
    ~QThinkGearDataHandler();
    static int dataCount;
    void pushData(TGData val);
    void addListener(QThinkGearListener *listener);
    void removeListener(QThinkGearListener *listener);
private:
    void receiveRaw(short val);
    void receiveEeg(TGData val);
signals:
    void onRaw(short val);
    void onBattery(unsigned char val);
    void onPoorSignal(unsigned char val);
    void onAttention(unsigned char val);
    void onMeditation(unsigned char val);
    void onEeg(EegValues val);
    void onConnecting(unsigned char val);
    void onReady(unsigned char val);
    void onError(unsigned char val);
    void onBlinkStrength(unsigned char val);
};

class QThinkGearListener : public QObject
{
    Q_OBJECT
public:
    QThinkGearListener(QObject *parent) : QObject(parent){}
public slots:
    virtual void onThinkGearRaw(short val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearBattery(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearPoorSignal(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearAttention(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearMeditation(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearEeg(EegValues val)
    { 
        qDebug() << __FUNCTION__;
        for (auto v : val.getAllValues()) {
            qDebug() << v.key() << ":" << v.value();
        } 
    }
    virtual void onThinkGearConnecting(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearReady(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearError(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    virtual void onThinkGearBlinkStrength(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
};
#endif // QTHINKGEARDATAHANDLER_H
