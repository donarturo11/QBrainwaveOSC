#include "SerialPortMonitor.h"
#include "ui_SerialPortMonitor.h"
#include <QList>

SerialPortMonitor::SerialPortMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortMonitor),
    tg(MainWindow::mainWindow()->thinkGear())
{
    ui->setupUi(this);
    connect(tg, SIGNAL(receivedData(QByteArray)),
            this, SLOT(onDataReceived(QByteArray)));
    initCursor();
}

SerialPortMonitor::~SerialPortMonitor()
{
    delete ui;
}

void SerialPortMonitor::initCursor()
{
    status_cursor = new QTextCursor(ui->status_text->textCursor());
}

void SerialPortMonitor::onDataReceived(QByteArray data)
{
    qDebug() << "onDataReceived " << data;
    QString msg;
    QTextStream stream(&msg);
    status_cursor->movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    stream << " 0x" << data.toHex() << ", ";
    status_cursor->insertText(msg);
}
