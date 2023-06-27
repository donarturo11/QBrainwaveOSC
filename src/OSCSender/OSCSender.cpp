#include "OSCSender.h"

OSCSender::OSCSender(QObject *parent) :
    QObject(parent),
    _tg{MainWindow::mainWindow()->thinkGear()}
{
    //_tg->addListener(this);
}

OSCSender::~OSCSender()
{

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


void OSCSender::onThinkGearRaw(short val)
{
    qDebug() << __PRETTY_FUNCTION__;
}

void OSCSender::onThinkGearBattery(unsigned char val)
{
    
}

void OSCSender::onThinkGearPoorSignal(unsigned char val)
{
    
}

void OSCSender::onThinkGearAttention(unsigned char val)
{
    
}

void OSCSender::onThinkGearMeditation(unsigned char val)
{
    
}

void OSCSender::onThinkGearEeg(EegValues val)
{
    
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
