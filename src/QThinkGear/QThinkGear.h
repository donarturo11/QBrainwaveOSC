#ifndef QTHINKGEAR_H
#define QTHINKGEAR_H
#include <QObject>
#include <QtCore>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "ThinkGearStreamParser.h"
#include "QThinkGearDataHandler.h"

const int ThinkgearBaudrates[] {
    9600, 57600
};

class QThinkGear : public QObject
{
    Q_OBJECT
public:
    QThinkGear(QObject *parent = nullptr);
    ~QThinkGear();
    static QThinkGear* qThinkGear() { return currentInstance; }
    void setPortName(QString portName) { _device.setPortName(portName); }
    void setBaudRate(int baudRate){ _device.setBaudRate(baudRate); }
    void open();
    void close();
    void test();
public slots:
    void onReadyRead();
signals:
    void receivedData(QByteArray data);
private:
    static QThinkGear* currentInstance;
protected:
    QSerialPort _device;
    ThinkGearStreamParser _parser;
    QThinkGearDataHandler _handler;
    
};
#endif // QTHINKGEAR_H
