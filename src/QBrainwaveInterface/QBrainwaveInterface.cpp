#include "QBrainwaveInterface.h"
#include <QtCore>
namespace Brainwave {
QBrainwaveInterface::QBrainwaveInterface(QObject *parent) :
    QObject(parent)
{
    qDebug() << "QBrainwaveInterface c-tor";
}

QBrainwaveInterface::~QBrainwaveInterface()
{
    qDebug() << "QBrainwaveInterface d-tor";
}

void QBrainwaveInterface::open()
{
    if (!_connection) return;
    _connection->open();
    emit connectionStatusChanged(_connection->connectionStatus());
}

void QBrainwaveInterface::close()
{
    if (!_connection) return;
    _connection->close();
    emit connectionStatusChanged(_connection->connectionStatus());
}

void QBrainwaveInterface::onBytesReceived(const unsigned char *bytes, int len)
{
    qDebug() << "payload lenght: " << len;
    for (int i=0; i<len; i++) {
        qDebug() << "[ " << i << " ] = " << bytes[i];
    }
    //_parser->parseBytes(bytes, len);
}

}