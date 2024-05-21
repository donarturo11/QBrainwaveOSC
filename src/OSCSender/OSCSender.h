#ifndef OSCSENDER_H
#define OSCSENDER_H
#include <QObject>
#include <QtCore>
#include "MainWindow.h"
#include "QBrainwaveInterface.h"
#include "QThinkGearDataHandler.h"
#include <QHostAddress>
#include <QUdpSocket>

#define OSCSENDER_ENABLE_RAW 0x01
#define OSCSENDER_ENABLE_EEG 0x02
#define OSCSENDER_ENABLE_ATTENTION 0x04
#define OSCSENDER_ENABLE_SIGNAL 0x08

class OSCSender : public QObject
{
    Q_OBJECT
public:
    OSCSender(QObject *parent = nullptr);
    ~OSCSender();
    void setAddress(const QString & address);
    void setPort(short port);
    void setFlags(int flags);
    void connectListener();
    void disconnectListener();
public slots:
    void onThinkGearRaw(short val);
    void onThinkGearBattery(unsigned char val);
    void onThinkGearPoorSignal(unsigned char val);
    void onThinkGearAttention(unsigned char val);
    void onThinkGearMeditation(unsigned char val);
    void onThinkGearEeg(EegValues val);
    void onThinkGearConnecting(unsigned char val);
    void onThinkGearReady(unsigned char val);
    void onThinkGearError(unsigned char val);
    void onThinkGearBlinkStrength(unsigned char val);
private:
    void sendDatagram(std::string path, std::string tag, uint32_t value);
    void sendFloatDatagram(std::string path, float value);
    void sendIntDatagram(std::string path, int value);
protected:
    QHostAddress _address;
    QUdpSocket *_socket;
    short _port;
    int _flags;
    Brainwave::QBrainwaveInterface *_brainwave;
    
};
#endif // OSCSENDER_H
