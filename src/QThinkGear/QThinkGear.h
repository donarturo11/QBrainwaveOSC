#ifndef QTHINKGEAR_H
#define QTHINKGEAR_H
#include <QObject>
#include <QtCore>
#include <QSerialPortInfo>
#include <QSerialPort>

const int ThinkgearBaudrates[] {
    1200, 2400, 4800, 9600, 57600, 115200
};

class QThinkGear : public QObject
{
    Q_OBJECT
public:
    QThinkGear(QObject *parent = nullptr);
    ~QThinkGear();
    static QThinkGear* qThinkGear() { return currentInstance; }
    void setPortName(QString portName) { device.setPortName(portName); }
    void setBaudRate(int baudRate){ device.setBaudRate(baudRate); }
    void open();
    void close();
public slots:
    void onReadyRead();
signals:
    void receivedData(QByteArray data);
private:
    static QThinkGear* currentInstance;
protected:
    QSerialPort device;
    
};
#endif // QTHINKGEAR_H
