#include "QBrainwaveInterface.h"
#include "SerialPortConnection.h"
#include <QtCore>
#include "parsers.h"
namespace Brainwave {
QBrainwaveInterface::QBrainwaveInterface(QObject *parent) :
    QObject(parent),
    _notifier(QBrainwaveNotifier(this)),
    _analyser(Brainwave::RawWaveAnalyser(512, 512, &_notifier)),
    _parser(nullptr),
    _connection(nullptr)
{}

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
    deleteParser();
    delete _connection;
    _connection = nullptr;
}

void QBrainwaveInterface::setupParser(QString name)
{
    // TODO: move all EEG devices to one registry
    if (name == "TwoByteRawParser") { 
        _parser = new TwoByteRawParser(&_notifier);
    }
    else if (name == "ThinkGearStreamParser") {
        _parser = new ThinkGearStreamParser(&_notifier);
    }
    else {
        qDebug() << "NoneParser";
    }
}
    
void QBrainwaveInterface::deleteParser()
{
    if (_parser) delete _parser;
    _parser = nullptr;
}

void QBrainwaveInterface::onRawWaveAnalyserEnabled()
{
    _notifier.enableRawWaveAnalyser();
    connect(&_notifier, SIGNAL(onRaw(float)), this, SLOT(putToAnalyser(float)));
}

void QBrainwaveInterface::onRawWaveAnalyserDisabled()
{
    _notifier.disableRawWaveAnalyser();
    disconnect(&_notifier, SIGNAL(onRaw(float)), this, SLOT(putToAnalyser(float)));
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
    //deleteConnection();
}

void QBrainwaveInterface::onBytesReceived(const char *bytes, int len)
{
    if (_parser)
        _parser->parseBytes(bytes, len);
}

}
