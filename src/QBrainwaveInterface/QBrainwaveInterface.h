#ifndef QBRAINWAVEINTERFACE_H
#define QBRAINWAVEINTERFACE_H
#include <QObject>
#include <QtCore>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "ThinkGearStreamParser.h"
#include "QThinkGearDataHandler.h"

#define BUFFER_SIZE 2048

const int ThinkgearBaudrates[] {
    57600, 9600
};
typedef enum {
    Idle,
    Reading,
    NoConnected
} BrainwaveInterfaceStatus;
class QBrainwaveInterface : public QObject
{
    Q_OBJECT
public:
    QBrainwaveInterface(QObject *parent = nullptr);
    ~QBrainwaveInterface();
    static QBrainwaveInterface* brainwaveInterface() { return currentInstance; }
    void addListener(QObject* listener) {
        _handler.addListener(listener); 
        }
    void removeListener(QObject* listener) { 
        _handler.removeListener(listener); 
        }
    void setPortName(QString portName) { _device.setPortName(portName); }
    void setBaudRate(int baudRate){ _device.setBaudRate(baudRate); }
    QString portName() { return _device.portName(); }
    int baudRate() { return _device.baudRate(); }
    bool opened() { return _opened; }
    BrainwaveInterfaceStatus status() { return _status; }
    void open();
    void close();
    void changeStatus(BrainwaveInterfaceStatus status);
    QSerialPort* device() { return &_device; }
public slots:
    void onReadyRead();
    void checkState();
signals:
    void receiveStatusChanged(int state);
    void statusChanged(BrainwaveInterfaceStatus status);
private:
    static QBrainwaveInterface* currentInstance;
protected:
    QSerialPort _device;
    bool _opened;
    ThinkGearStreamParser _parser;
    QThinkGearDataHandler _handler;
    BrainwaveInterfaceStatus _status;
};
#endif // QBRAINWAVEINTERFACE_H
