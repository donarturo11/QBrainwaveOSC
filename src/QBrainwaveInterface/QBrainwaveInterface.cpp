#include "QBrainwaveInterface.h"
#include "SerialPortConnection.h"
#include <QtCore>
#include "parsers.h"
namespace Brainwave {
QBrainwaveInterface::QBrainwaveInterface(QObject *parent) :
    QObject(parent),
    _notifier(QBrainwaveNotifier(this)),
    _analyser(Brainwave::RawWaveAnalyser(512, &_notifier)),
    _parser(nullptr),
    _connection(nullptr)
{
    _analyser.setSamplerate(512);
}

QBrainwaveInterface::~QBrainwaveInterface()
{
    close();
}

void QBrainwaveInterface::setupConnection(QVariantMap args)
{
    if (args["porttype"] == QVariant("serial")) _connection = new SerialPortConnection(this);
    else qDebug() << "Port" << args["porttype"] << "not implemented";
    if (_connection) {
        connect(_connection,
                SIGNAL(connectionStatusChanged(Brainwave::Device::ConnectionStatus)),
                this,
                SLOT(onConnectionStatusChanged(Brainwave::Device::ConnectionStatus))
                );
        _connection->setupConnection(args);
        setupParser(args["type"].toString());
    }
}

void QBrainwaveInterface::deleteConnection()
{
    if (!_connection) return;
    disconnect(_connection,
               SIGNAL(connectionStatusChanged(Brainwave::Device::ConnectionStatus)),
               this,
               SLOT(onConnectionStatusChanged(Brainwave::Device::ConnectionStatus))
               );
    delete _connection;
    _connection = nullptr;
}

void QBrainwaveInterface::setupParser(QString name)
{
    if (name == "TwoByteRawParser") { 
        _parser = new TwoByteRawParser(&_notifier);
        connect(&_notifier, SIGNAL(onRaw(float)), this, SLOT(pushToAnalyser(float)));
    }
    else if (name == "ThinkGearStreamParser") {
        _parser = new ThinkGearStreamParser(&_notifier);
    }
}
    
void QBrainwaveInterface::deleteParser()
{
    if (_parser) delete _parser;
    _parser = nullptr;
    disconnect(&_notifier, SIGNAL(onRaw(float)), this, SLOT(pushToAnalyser(float)));
}

void QBrainwaveInterface::open()
{
    if (!_connection) return;
    connect(_connection, SIGNAL(bytesReceived(const char*,int)),
            this, SLOT(onBytesReceived(const char*,int)));
    _connection->open();
    //emit connectionStatusChanged(_connection->connectionStatus());
}

void QBrainwaveInterface::close()
{
    if (!_connection) return;
    _connection->close();
    disconnect(_connection, SIGNAL(bytesReceived(const char*,int)),
            this, SLOT(onBytesReceived(const char*,int)));
    //emit connectionStatusChanged(_connection->connectionStatus());
    deleteConnection();
    deleteParser();
}

void QBrainwaveInterface::onBytesReceived(const char *bytes, int len)
{
    if (_parser)
        _parser->parseBytes(bytes, len);
}

}
