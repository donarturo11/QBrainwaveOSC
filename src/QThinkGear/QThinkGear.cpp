#include "QThinkGear.h"

QThinkGear* QThinkGear::currentInstance;

QThinkGear::QThinkGear(QObject *parent) :
    QObject(parent)
{
    qDebug() << "QThinkGear c-tor";
    connect(&_device, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    _device.setReadBufferSize(BUFFER_SIZE);
    QThinkGear::currentInstance = this;
    THINKGEAR_initParser(&_parser, PARSER_TYPE_PACKETS, QThinkGearDataHandle, &_handler);
    _status = ThinkGearStatus::NoConnected;
    _opened = false;
}

QThinkGear::~QThinkGear()
{
    QThinkGear::currentInstance = nullptr;
}

void QThinkGear::open()
{
#ifdef QT6
    _opened = _device.open(QIODeviceBase::ReadWrite);
#else
    _opened = _device.open(QIODevice::ReadWrite);
#endif
    if (_opened) {
        _device.flush();
        changeStatus(ThinkGearStatus::Idle);
    } 
    else {
        changeStatus(ThinkGearStatus::NoConnected);
    }
}

void QThinkGear::close()
{
    _device.flush();
    _device.close();
    _opened = false;
    changeStatus(ThinkGearStatus::NoConnected);
}

void QThinkGear::onReadyRead()
{
    int bufsize = _device.readBufferSize();
    char buffer[bufsize];
    int size = _device.bytesAvailable();
    if (size) {
        changeStatus(ThinkGearStatus::Reading);
    }
    int state = 0;
    _device.read(buffer, bufsize);
    for (int i=0; i<size; i++) {
        state = THINKGEAR_parseByte(&_parser, buffer[i]);
    }
    emit receiveStatusChanged(state);
    checkState();
}

void QThinkGear::checkState()
{
    if (!_device.waitForReadyRead(10)) {
       changeStatus(ThinkGearStatus::Idle);
       close();
       open();
       emit receiveStatusChanged(0);
    }
}

void QThinkGear::changeStatus(ThinkGearStatus status)
{
    _status = status;
    emit statusChanged(status);
}
