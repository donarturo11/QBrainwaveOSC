#include "DeviceConfiguration.h"
#include "ui_DeviceConfiguration.h"
#include "MainWindow.h"
#include <QList>
#include <QSerialPortInfo>
DeviceConfiguration::DeviceConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceConfiguration),
    status(Status::NOT_READY),
    tg(QThinkGear::qThinkGear())
{
    ui->setupUi(this);
    connect(ui->refresh_btn, SIGNAL(clicked()),
            this, SLOT(refresh()));
    connect(ui->connect_btn, SIGNAL(clicked()),
            this, SLOT(connectDevice()));
    connect(ui->disconnect_btn, SIGNAL(clicked()),
            this, SLOT(disconnectDevice()));
    connect(ui->devices_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseDevice(int)));
    connect(ui->baudrates_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseBaudrate(int)));

    initBaudRates();
    refresh();

}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}

void DeviceConfiguration::initBaudRates()
{
    for (auto bRate : ThinkgearBaudrates) {
        ui->baudrates_cb->addItem(QString::number(bRate), bRate);
    }
}

void DeviceConfiguration::chooseDevice(int id)
{
    auto portName = ui->devices_cb->currentData().toString();
    tg->setPortName(portName);
}

void DeviceConfiguration::chooseBaudrate(int id)
{
    int bRate = ui->baudrates_cb->currentData().toInt();
    qDebug() << "[DeviceConfiguration] choosed baudrate" << bRate;
    tg->setBaudRate(bRate);
}



void DeviceConfiguration::refresh()
{
    qDebug() << "DeviceConfiguration::refresh()";
    auto ports = QSerialPortInfo::availablePorts();
    ui->devices_cb->clear();
    for (auto port : ports) {
        auto portName = port.portName();
        ui->devices_cb->addItem(portName, portName);
    }
}