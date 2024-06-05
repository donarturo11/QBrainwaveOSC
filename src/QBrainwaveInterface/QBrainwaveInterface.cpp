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
    qDebug() << "QBrainwaveInterface c-tor";
    _analyser.setSamplerate(512);
}

QBrainwaveInterface::~QBrainwaveInterface()
{
    qDebug() << "QBrainwaveInterface d-tor";
    close();
    deleteConnection();
    deleteParser();
}

void QBrainwaveInterface::setupConnection(QVariantMap args)
{
    qDebug() << "QBrainwaveInterface: " << __FUNCTION__;
    if (args["porttype"] == QVariant("serial")) _connection = new SerialPortConnection(this);
    else qDebug() << "Port" << args["porttype"] << "not implemented";
    if (_connection) {
        _connection->setupConnection(args);
        setupParser(args["type"].toString());
    }
}

void QBrainwaveInterface::deleteConnection()
{
    qDebug() << "QBrainwaveInterface: " << __FUNCTION__;
    if (_connection) delete _connection;
    _connection = nullptr;
}

void QBrainwaveInterface::setupParser(QString name)
{
    qDebug() << "Setup parser: " << name;
}
    
void QBrainwaveInterface::deleteParser()
{
    if (_parser) delete _parser;
    _parser = nullptr;
}

void QBrainwaveInterface::open()
{
    qDebug() << "QBrainwaveInterface: " << __FUNCTION__;
    if (!_connection) return;
    connect(_connection, SIGNAL(bytesReceived(const char*,int)),
            this, SLOT(onBytesReceived(const char*,int)));
    _connection->open();
    emit connectionStatusChanged(_connection->connectionStatus());
}

void QBrainwaveInterface::close()
{
    qDebug() << "QBrainwaveInterface: " << __FUNCTION__;
    if (!_connection) return;
    _connection->close();
    disconnect(_connection, SIGNAL(bytesReceived(const char*,int)),
            this, SLOT(onBytesReceived(const char*,int)));
    emit connectionStatusChanged(_connection->connectionStatus());
}

void QBrainwaveInterface::onBytesReceived(const char *bytes, int len)
{
    qDebug() << "payload lenght: " << len;
    qDebug() << QByteArray(bytes, len).toHex(' ');
    //_parser->parseBytes(bytes, len);
}

}
