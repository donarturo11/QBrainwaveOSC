#ifndef THINKGEAR_H
#define THINKGEAR_H
#include <QObject>
#include <QtCore>
#include <QSerialPortInfo>
#include <QSerialPort>

const int ThinkgearBaudrates[] {
    1200, 2400, 4800, 9600, 57600, 115200
};

class ThinkGear : public QObject
{
    Q_OBJECT
public:
    ThinkGear(QObject *parent = nullptr);
    ~ThinkGear();
    void setPortName(QString portName) { device.setPortName(portName); }
    void setBaudRate(int baudRate){ device.setBaudRate(baudRate); }
    void open();
    void close();
public slots:
    void onReadyRead();
signals:
    void receivedData(QByteArray data);
protected:
    QSerialPort device;
    
};
#endif // THINKGEAR_H
