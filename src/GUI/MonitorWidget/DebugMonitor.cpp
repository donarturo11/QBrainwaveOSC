#include "DebugMonitor.h"
#include "ui_DebugMonitor.h"
#include <QList>
//#include <QStringStream>

DebugMonitor::DebugMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugMonitor)
{
    ui->setupUi(this);
    mainwindow = MainWindow::mainWindow();
    connect(mainwindow, SIGNAL(debugReceived(QString)),
            this, SLOT(onDebugReceived(QString)));
    initCursor();
}

DebugMonitor::~DebugMonitor()
{
    delete ui;
}

void DebugMonitor::initCursor()
{
    status_cursor = new QTextCursor(ui->status_text->textCursor());
}

void DebugMonitor::onDebugReceived(QString dbgString)
{
    fprintf(stderr, "DebugMonitor::onDebugReceived\n");
    QString msg;
    QTextStream stream(&msg);
    status_cursor->movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    stream << "qDebug: " << dbgString << "\n";
    status_cursor->insertText(msg);
}
