#ifndef QTHINKGEAR_H
#define QTHINKGEAR_H
#include <QObject>
#include <QtCore>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "ThinkGearStreamParser.h"
#include "QThinkGearDataHandler.h"

const int ThinkgearBaudrates[] {
    57600, 9600
};
typedef enum {
    Idle,
    Success,
    Fail
} TGConnectionStatus;
class QThinkGear : public QObject
{
    Q_OBJECT
public:
    QThinkGear(QObject *parent = nullptr);
    ~QThinkGear();
    static QThinkGear* qThinkGear() { return currentInstance; }
    void addListener(QObject* listener) {
        _handler.addListener(listener); 
        }
    void removeListener(QObject* listener) { 
        _handler.removeListener(listener); 
        }
    void setPortName(QString portName) { _device.setPortName(portName); }
    void setBaudRate(int baudRate){ _device.setBaudRate(baudRate); }
    void open();
    void close();
    void test();
    void changeStatus(TGConnectionStatus status);
public slots:
    void onReadyRead();
signals:
    void receivedData(QByteArray data);
    void statusChanged(TGConnectionStatus status);
private:
    static QThinkGear* currentInstance;
protected:
    QSerialPort _device;
    ThinkGearStreamParser _parser;
    QThinkGearDataHandler _handler;
    TGConnectionStatus _status;
    
};
#endif // QTHINKGEAR_H
