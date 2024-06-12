#ifndef BRAINWAVE_CONNECTIONSTATUS_H
#define BRAINWAVE_CONNECTIONSTATUS_H

#include <QString>
#include <QHash>

namespace Brainwave {
namespace Device {

typedef enum {
    ConnectionFailed = -1,
    NoConnected,
    Idle,
    Connected,
    Reading,
    Writing
} ConnectionStatus;

const inline QHash<ConnectionStatus,QString> ConnectionStatusMsg =
{
    {ConnectionStatus::ConnectionFailed, "FAILED"},
    {ConnectionStatus::NoConnected, "No connected"},
    {ConnectionStatus::Idle, "Idle"},
    {ConnectionStatus::Connected, "Connected"},
    {ConnectionStatus::Reading, "Reading"},
    {ConnectionStatus::Writing, "Writing"}
};

class ConnectionStatusMessage
{
public:
    ConnectionStatusMessage(Brainwave::Device::ConnectionStatus status) {
        _status = status;
        _msg = "";
        _msg += "Connection status: ";
        _msg += ConnectionStatusMsg[status];
        _msg += ".";
    }
    ~ConnectionStatusMessage(){}
    QString msg() const { return _msg; }
    Brainwave::Device::ConnectionStatus status() const { return _status; }
private:
    Brainwave::Device::ConnectionStatus  _status;
    QString _msg;
};
} // namespace Device
} // namespace Brainwave
#endif
