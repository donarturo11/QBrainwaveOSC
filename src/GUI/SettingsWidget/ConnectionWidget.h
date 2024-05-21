#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H
#include <QWidget>
#include "QBrainwaveInterface.h"

namespace Ui {
class ConnectionWidget;
}

class ConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWidget(QWidget *parent = nullptr);
    ~ConnectionWidget();
public slots:
    void onConnectionStatusChanged(Brainwave::ConnectionStatus);
    void onParametersReceived(QVariantMap);
    void connectDevice();
    void disconnectDevice();
signals:
    void parametersQuery();
private:
    Ui::ConnectionWidget *ui;
    Brainwave::QBrainwaveInterface *_brainwave;
    QVariantMap _parameters;
    bool _ready;
};

#endif // CONNECTIONWIDGET_H
