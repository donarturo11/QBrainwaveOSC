#ifndef QBRAINWAVEINTERFACE_H
#define QBRAINWAVEINTERFACE_H
#include <QObject>
#include <QtCore>
#include "DeviceConnection.h"
namespace Brainwave {
class QBrainwaveInterface : public QObject
{
    Q_OBJECT
public:
    QBrainwaveInterface(QObject *parent = nullptr);
    ~QBrainwaveInterface();
    void open();
    void close();
    void addListener(QObject* listener) {
        //_notifier.addListener(listener);
        qDebug() << "Add listener";
        }
    void removeListener(QObject* listener) {
        //_notifier.removeListener(listener);
        qDebug() << "Remove listener";
        }
public slots:
    void onBytesReceived(const unsigned char *bytes, int len);
signals:
    void connectionStatusChanged(Brainwave::ConnectionStatus status);
protected:
    DeviceConnection *_connection;
    DataParser *_parser;
    void *_notifier;
    void *_analyser;
};
}
#endif // QTHINKGEAR_H
