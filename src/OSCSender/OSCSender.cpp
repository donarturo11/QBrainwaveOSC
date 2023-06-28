#include "OSCSender.h"
#include "OSCMessage.h"

OSCSender::OSCSender(QObject *parent) :
    QObject(parent),
    _tg{MainWindow::mainWindow()->thinkGear()}
{
    _socket = new QUdpSocket(this);
}

OSCSender::~OSCSender()
{
    delete _socket;
}

void OSCSender::connectListener()
{
    _tg->addListener(this);
}

void OSCSender::disconnectListener()
{
    _tg->removeListener(this);
}

void OSCSender::setAddress(const QString& address)
{
    _address = QHostAddress(address);
}

void OSCSender::setPort(short port)
{   
    _port = port;
}

void OSCSender::setFlags(int flags)
{
    _flags = flags;
}

void OSCSender::sendDatagram(std::string path, std::string tag, uint32_t value)
{
    auto msg = OSCMessage(path, tag, value).data();
    _socket->writeDatagram(msg.data(), msg.size(), _address, _port);
}

void OSCSender::sendFloatDatagram(std::string path, float value)
{
    union {
        float f;
        uint32_t i;
    } val;
    val.f = value;
    sendDatagram(path, ",f", val.i);
}

void OSCSender::sendIntDatagram(std::string path, int value)
{
    sendDatagram(path, ",i", value);
}

void OSCSender::onThinkGearRaw(short val)
{
    if (!(_flags&OSCSENDER_ENABLE_RAW)) return;
    sendIntDatagram("/raw", val);
}

void OSCSender::onThinkGearBattery(unsigned char val)
{
    
}

void OSCSender::onThinkGearPoorSignal(unsigned char val)
{
    if (!(_flags&OSCSENDER_ENABLE_SIGNAL)) return;
    sendFloatDatagram("/signal", val/200.00);
}

void OSCSender::onThinkGearAttention(unsigned char val)
{
    if (!(_flags&OSCSENDER_ENABLE_ATTENTION)) return;
    sendFloatDatagram("/attention", val/100.00);
}

void OSCSender::onThinkGearMeditation(unsigned char val)
{
    if (!(_flags&OSCSENDER_ENABLE_ATTENTION)) return;
    sendFloatDatagram("/meditation", val/100.00);
}

void OSCSender::onThinkGearEeg(EegValues val)
{
    if (!(_flags&OSCSENDER_ENABLE_EEG)) return;
    auto allValues = val.getAllValues();
    for (auto v : allValues) {
        std::string path = "/" + v.key();
        float value = v.value()/(float) val.sum();
        sendFloatDatagram(path, value);
    }
}

void OSCSender::onThinkGearConnecting(unsigned char val)
{
    
}

void OSCSender::onThinkGearReady(unsigned char val)
{
    
}

void OSCSender::onThinkGearError(unsigned char val)
{
    
}

void OSCSender::onThinkGearBlinkStrength(unsigned char val)
{
    
}
