#include "DeviceConfiguration.h"
#include "ui_DeviceConfiguration.h"
#include <QList>
DeviceConfiguration::DeviceConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceConfiguration)
{
    ui->setupUi(this);
    connect(ui->refresh_btn, SIGNAL(clicked()), this, SLOT(refreshDevices()));
    connect(ui->connect_btn, SIGNAL(clicked()), this, SLOT(connectDevice()));
    connect(ui->disconnect_btn, SIGNAL(clicked()), this, SLOT(disconnectDevice()));
    connect(ui->devices_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseDevice(int)));
    connect(ui->baudrates_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseBaudrate(int)));
    devices << "dev1" << "dev2" << "dev3";
}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}
void DeviceConfiguration::refreshDevices()
{
    auto devices_cb = ui->devices_cb;
    devices_cb->clear();
    devices_cb->addItems(devices);
    qDebug() << "discovery->getDevicesList(devices_list) QBluetoothDeviceInfo name [mac address]";
    qDebug() << "discovery->getBaudratesList(devices_list)";
}



void DeviceConfiguration::connectDevice()
{
    if (devices.empty()) return;
    auto devices_cb = ui->devices_cb;
    int devId=devices_cb->currentIndex();
    QString name = devices[devId];
    emit connectionRequest(name);
}

void DeviceConfiguration::disconnectDevice()
{
    emit disconnectionRequest();
}

void DeviceConfiguration::chooseDevice(int id)
{
    if (devices.empty()) return;
    qDebug() << "[DeviceConfiguration] choosed device[" << id
             <<  "]" << devices[id];
}

void DeviceConfiguration::chooseBaudrate(int id)
{
    qDebug() << "[DeviceConfiguration] choosed baudrate[" << id
             <<  "]" ; //<< devices[id];
}
