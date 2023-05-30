#include "QThinkGear.h"
#include "thinkgear_test_packets.h"
QThinkGear* QThinkGear::currentInstance;

QThinkGear::QThinkGear(QObject *parent) :
    QObject(parent)
{
    qDebug() << "QThinkGear c-tor";
    connect(&device, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    device.setReadBufferSize(512);
    QThinkGear::currentInstance = this;
}

QThinkGear::~QThinkGear()
{
    QThinkGear::currentInstance = nullptr;
}

void QThinkGear::open()
{
    qDebug() << "ThinkGear: connect to : "
             << device.portName() << "@" 
             << device.baudRate();
#ifdef QT6
    bool opened = device.open(QIODeviceBase::ReadWrite);
#else
    bool opened = device.open(QIODevice::ReadWrite);
#endif
    if (opened) qDebug() << "Open SUCCESS";
    else qDebug() << "Open FAILED";
}

void QThinkGear::close()
{
    qDebug() << "ThinkGear::disconnect";
    device.flush();
    device.close();
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
    qDebug() << "[ThinkGear] readData " << device.readBufferSize();
    auto data = device.read(device.readBufferSize());
    emit receivedData(data);
}