#include "OSCSender.h"
#include "OSCMessage.h"

OSCSender::OSCSender(QObject *parent) :
    QObject(parent),
    _brainwave{MainWindow::mainWindow()->brainwaveInterface()}
{
    _socket = new QUdpSocket(this);
}

OSCSender::~OSCSender()
{
    if (_brainwave) disconnectListener();
    delete _socket;
}

void OSCSender::connectListener()
{
    _brainwave->addListener(this);
}

void OSCSender::disconnectListener()
{
    _brainwave->removeListener(this);
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

void OSCSender::onRaw(float val)
{
    if (!(_flags&OSCSENDER_ENABLE_RAW)) return;
    sendFloatDatagram("/raw", (int)(val*2048));
}

void OSCSender::onBattery(float val)
{
    sendFloatDatagram("/battery", val);
}

void OSCSender::onPoorSignal(float val)
{
    if (!(_flags&OSCSENDER_ENABLE_SIGNAL)) return;
    sendFloatDatagram("/signal", val);
}

void OSCSender::onAttention(float val)
{
    if (!(_flags&OSCSENDER_ENABLE_ATTENTION)) return;
    sendFloatDatagram("/attention", val);
}

void OSCSender::onMeditation(float val)
{
    if (!(_flags&OSCSENDER_ENABLE_ATTENTION)) return;
    sendFloatDatagram("/meditation", val);
}

void OSCSender::onEeg(Brainwave::EegBands eeg)
{
    if (!(_flags&OSCSENDER_ENABLE_EEG)) return;
    sendFloatDatagram("/eegdelta", eeg.delta);
    sendFloatDatagram("/eegtheta", eeg.theta);
    sendFloatDatagram("/eeglowalpha", eeg.lowAlpha);
    sendFloatDatagram("/eeghighalpha", eeg.highAlpha);
    sendFloatDatagram("/eeglowbeta", eeg.lowBeta);
    sendFloatDatagram("/eeghighbeta", eeg.highBeta);
    sendFloatDatagram("/eeglowgamma", eeg.lowGamma);
    sendFloatDatagram("/eeghighgamma", eeg.highGamma);
}

void OSCSender::onBlinkStrength(float val)
{
    sendFloatDatagram("/blinkstrength", val);
}

/*
void OSCSender::onConnecting(unsigned char val)
{
    
}

void OSCSender::onReady(unsigned char val)
{
    
}

void OSCSender::onError(unsigned char val)
{
    
}
*/
