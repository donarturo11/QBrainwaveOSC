#include "DeviceConfiguration.h"
#include "ui_DeviceConfiguration.h"
#include "MainWindow.h"
#include <QList>
#include <QSerialPortInfo>
DeviceConfiguration::DeviceConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceConfiguration),
    status(Status::NOT_READY),
    tg(MainWindow::mainWindow()->thinkGear())
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
            this, SLOT(chooseBaudRate(int)));
    connect(ui->types_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseType(int)));
    connect(tg, SIGNAL(statusChanged(ThinkGearStatus)),
            this, SLOT(onThinkGearStatusChanged(ThinkGearStatus)));
    setupDeviceTypes();
    refresh();

}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}

void DeviceConfiguration::setupBaudRates()
{
    int idx = ui->types_cb->currentIndex();
    ui->baudrates_cb->clear();
    for (auto bRate : TGTypes[idx].baudrates) {
        ui->baudrates_cb->addItem(QString::number(bRate), bRate);
    }
}

void DeviceConfiguration::chooseDevice(int id)
{
    auto portName = ui->devices_cb->currentData().toString();
    tg->setPortName(portName);
}

void DeviceConfiguration::chooseBaudRate(int id)
{
    int bRate = ui->baudrates_cb->currentData().toInt();
    tg->setBaudRate(bRate);
}



void DeviceConfiguration::refresh()
{
    auto ports = QSerialPortInfo::availablePorts();
    ui->devices_cb->clear();
    for (auto port : ports) {
        auto portName = port.portName();
        ui->devices_cb->addItem(portName, portName);
    }
}

void DeviceConfiguration::setupDeviceTypes()
{
    for (auto dev : TGTypes) {
        auto devName = QString(dev.name.c_str());
        ui->types_cb->addItem(devName, devName);
    }
}

void DeviceConfiguration::onThinkGearStatusChanged(ThinkGearStatus status)
{}

void DeviceConfiguration::chooseType(int id)
{
    tg->setupDeviceType(id);
    setupBaudRates();
}