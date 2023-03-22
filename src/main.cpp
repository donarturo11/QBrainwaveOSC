#include "MainWindow.h"
#include <iostream>
#include <QApplication>

void qDebugHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    auto mainWindow = MainWindow::mainWindow();
    if (!mainWindow) return;
    mainWindow->onDebugReceived(msg);
    std::cout << msg.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(qDebugHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
