#include "QThinkGear.h"
#include "thinkgear_test_packets.h"
QThinkGear* QThinkGear::currentInstance;

QThinkGear::QThinkGear(QObject *parent) :
    QObject(parent)
{
    qDebug() << "QThinkGear c-tor";
    connect(&_device, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    _device.setReadBufferSize(512);
    QThinkGear::currentInstance = this;
    THINKGEAR_initParser(&_parser, PARSER_TYPE_PACKETS, QThinkGearDataHandle, &_handler);
    _status = TGConnectionStatus::Idle;
}

QThinkGear::~QThinkGear()
{
    QThinkGear::currentInstance = nullptr;
}

void QThinkGear::open()
{
    qDebug() << "ThinkGear: connect to : "
             << _device.portName() << "@" 
             << _device.baudRate();
#ifdef QT6
    bool opened = _device.open(QIODeviceBase::ReadWrite);
#else
    bool opened = _device.open(QIODevice::ReadWrite);
#endif
    if (opened) {
        changeStatus(TGConnectionStatus::Success);
    } 
    else {
        changeStatus(TGConnectionStatus::Fail);
    }
}

void QThinkGear::close()
{
    qDebug() << "ThinkGear::disconnect";
    _device.flush();
    _device.close();
    changeStatus(TGConnectionStatus::Idle);
}

void QThinkGear::test()
{
    QByteArray data;
    for (int i=0; i<raw_wave_len; i++) {
        data.push_back(raw_wave[i]);
    }
    for (int i=0; i<eeg_packet_len; i++) {
        data.push_back(eeg_packet1[i]);
    }
    for (int i=0; i<eeg_packet_len; i++) {
        data.push_back(eeg_packet2[i]);
    }
    for (int i=0; i<eeg_packet_len; i++) {
        data.push_back(eeg_packet3[i]);
    }
    emit receivedData(data);
}

void QThinkGear::onReadyRead()
{
    int bufsize = _device.readBufferSize();
    char buffer[1024];
    int size = _device.bytesAvailable();
    _device.read(buffer, bufsize);
    for (int i=0; i<size; i++) {
        THINKGEAR_parseByte(&_parser, buffer[i]);
    }
}

void QThinkGear::changeStatus(TGConnectionStatus status)
{
    _status = status;
    emit statusChanged(status);
}
