#include "DeviceConfiguration.h"
#include "ui_DeviceConfiguration.h"
#include <QList>
DeviceConfiguration::DeviceConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceConfiguration),
    status(Status::NOT_READY),
    bt_discovery(new DeviceDiscovery(this))
{
    ui->setupUi(this);
    connect(ui->refresh_btn, SIGNAL(clicked()), this, SLOT(refreshDevices()));
    connect(ui->connect_btn, SIGNAL(clicked()), this, SLOT(connectDevice()));
    connect(ui->disconnect_btn, SIGNAL(clicked()), this, SLOT(disconnectDevice()));
    connect(ui->devices_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseDevice(int)));
    connect(ui->baudrates_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseBaudrate(int)));

    connect(bt_discovery, SIGNAL(finished()), this, SLOT(onDiscoveryFinished()));
    
    
    refreshDevices();
    
}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}
void DeviceConfiguration::refreshDevices()
{
    status = Status::SEARCHING;
    qDebug() << "DeviceConfiguration: Bluetooth manager " << BluetoothManager::bluetoothManager();
    bt_discovery->refresh();
}



void DeviceConfiguration::connectDevice()
{
    if (status != Status::READY) return;
    auto devices_cb = ui->devices_cb;
    int devId=devices_cb->currentIndex();
    QString address = bt_devices[devId].address().toString();
    emit connectionRequest(address);
}

void DeviceConfiguration::disconnectDevice()
{
    emit disconnectionRequest();
}

void DeviceConfiguration::chooseDevice(int id)
{
    if (status != Status::READY) return;
    qDebug() << "[DeviceConfiguration] choosed device[" << id
             <<  "]" << bt_devices[id].name() << " " << bt_devices[id].address();
}

void DeviceConfiguration::chooseBaudrate(int id)
{
    qDebug() << "[DeviceConfiguration] choosed baudrate[" << id
             <<  "]" ; //<< devices[id];
}

void DeviceConfiguration::onDiscoveryFinished()
{
    qDebug() << "Discovery finished";
    bt_devices.clear();
    ui->devices_cb->clear();
    bt_devices = bt_discovery->getDevicesList();
    for (auto dev : bt_devices) {
        QString nameItem = dev.name() + " " + dev.address().toString();
        ui->devices_cb->addItem(nameItem);
    }
    status = Status::READY;
    emit statusNotify(status);
}
