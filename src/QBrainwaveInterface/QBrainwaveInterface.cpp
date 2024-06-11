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
    /* Temporary notifier debug */
    //connect(&_notifier, &QBrainwaveNotifier::onRaw, [](float v){ qDebug() << "Raw: " << v ; });
    connect(&_notifier, &QBrainwaveNotifier::onBattery, [](float v){ qDebug() << "Battery: " << v ; });
    connect(&_notifier, &QBrainwaveNotifier::onPoorSignal, [](float v){ qDebug() << "PoorSignal: " << v ; });
    connect(&_notifier, &QBrainwaveNotifier::onAttention, [](float v){ qDebug() << "Attention: " << v ; });
    connect(&_notifier, &QBrainwaveNotifier::onMeditation, [](float v){ qDebug() << "Meditation: " << v ; });
    connect(&_notifier, &QBrainwaveNotifier::onEeg, 
            [](EegBands eeg){ 
                qDebug() << "Eeg: " ;
                qDebug() << "Delta\t\t" << eeg.delta;
                qDebug() << "theta\t\t" << eeg.theta;
                qDebug() << "Low Alpha\t" << eeg.lowAlpha;
                qDebug() << "High Alpha\t" << eeg.highAlpha;
                qDebug() << "Low Beta\t" << eeg.lowBeta;
                qDebug() << "High Beta\t" << eeg.highBeta;
                qDebug() << "Low Gamma\t" << eeg.lowGamma;
                qDebug() << "High Gamma\t" << eeg.highGamma;
                });
    /* ************************* */
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
    deleteConnection();
    deleteParser();
}

void QBrainwaveInterface::onBytesReceived(const char *bytes, int len)
{
    if (_parser)
        _parser->parseBytes(bytes, len);
}

}
