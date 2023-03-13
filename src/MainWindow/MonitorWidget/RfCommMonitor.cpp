#include "RfCommMonitor.h"
#include "ui_RfCommMonitor.h"
#include <QList>
//#include <QStringStream>

RfCommMonitor::RfCommMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RfCommMonitor),
    listener(BluetoothManager::bluetoothManager()->btListener())
{
    ui->setupUi(this);
    connect(listener, SIGNAL(receivedData(QByteArray)), this, SLOT(onDataReceived(QByteArray)));
    initCursor();
}

RfCommMonitor::~RfCommMonitor()
{
    delete ui;
}

void RfCommMonitor::initCursor()
{
    status_cursor = new QTextCursor(ui->status_text->textCursor());
}

void RfCommMonitor::onDataReceived(QByteArray data)
{
    QString msg;
    QTextStream stream(&msg);
    status_cursor->movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    stream << " 0x" << data.toHex() << ", ";
    status_cursor->insertText(msg);
}