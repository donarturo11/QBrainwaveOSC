#ifndef QBRAINWAVEINTERFACE_H
#define QBRAINWAVEINTERFACE_H
#include <QObject>
#include <QtCore>
#include "QBrainwaveNotifier.h"
#include "RawWaveAnalyser.h"
#include "DeviceConnection.h"
namespace Brainwave {
class QBrainwaveInterface : public QObject
{
    Q_OBJECT
public:
    QBrainwaveInterface(QObject *parent = nullptr);
    ~QBrainwaveInterface();
    void setupConnection(QVariantMap);
    void deleteConnection();
    void setupParser(QString);
    void deleteParser();
    void open();
    void close();
    void addListener(QObject* listener) {
        _notifier.addListener(listener);
        }
    void removeListener(QObject* listener) {
        _notifier.removeListener(listener);
        }
public slots:
    void onBytesReceived(const char *bytes, int len);
    void putToAnalyser(float v) { _analyser.put(v); }
    void onConnectionStatusChanged(Brainwave::Device::ConnectionStatus status) {
        emit connectionStatusChanged(status);
    }
    void onRawWaveAnalyserEnabled();
    void onRawWaveAnalyserDisabled();
signals:
    void connectionStatusChanged(Brainwave::Device::ConnectionStatus status);
protected:
    DeviceConnection *_connection;
    DataParser *_parser;
    Brainwave::QBrainwaveNotifier _notifier;
    RawWaveAnalyser _analyser;
};
}
#endif // QTHINKGEAR_H
