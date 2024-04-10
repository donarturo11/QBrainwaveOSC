#ifndef QTHINKGEAR_H
#define QTHINKGEAR_H
#include <QObject>
#include <QtCore>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "ThinkGearStreamParser.h"
#include "QThinkGearDataHandler.h"

#define BUFFER_SIZE 2048

typedef struct _ThinkgearDeviceType {
    std::string name;
    std::vector<int> baudrates;
    unsigned char parsertype;
    void (*dataHandle)(unsigned char extendedCodeLevel,
                       unsigned char code,
                       unsigned char numBytes,
                       const unsigned char *value,
                       void *customData );
} ThinkgearDeviceType;

const ThinkgearDeviceType TGTypes[] {
    {"Neurosky ThinkGear", {57600, 9600}, PARSER_TYPE_PACKETS, QThinkGearDataHandle},
    {"2-byte raw wave (unsigned)", {38400, 9600}, PARSER_TYPE_2BYTERAW, QTwoByteRawDataHandle }
};

typedef enum {
    Idle,
    Reading,
    NoConnected
} ThinkGearStatus;
class QThinkGear : public QObject
{
    Q_OBJECT
public:
    QThinkGear(QObject *parent = nullptr);
    ~QThinkGear();
    void setupDeviceType(int id);
    static QThinkGear* qThinkGear() { return currentInstance; }
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
    ThinkGearStatus status() { return _status; }
    void open();
    void close();
    void changeStatus(ThinkGearStatus status);
    QSerialPort* device() { return &_device; }
public slots:
    void onReadyRead();
    void checkState();
signals:
    void receiveStatusChanged(int state);
    void statusChanged(ThinkGearStatus status);
private:
    static QThinkGear* currentInstance;
protected:
    QSerialPort _device;
    bool _opened;
    ThinkGearStreamParser _parser;
    QThinkGearDataHandler _handler;
    ThinkGearStatus _status;
};
#endif // QTHINKGEAR_H
