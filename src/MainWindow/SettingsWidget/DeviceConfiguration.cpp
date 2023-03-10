#include "DeviceConfiguration.h"
#include "ui_DeviceConfiguration.h"
#include <QList>
DeviceConfiguration::DeviceConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceConfiguration),
    status(Status::NOT_READY),
    bt_manager(BluetoothManager::bluetoothManager())
{
    ui->setupUi(this);
    /*
    connect(ui->refresh_btn, SIGNAL(clicked()), this, SLOT(refreshDevices()));
    connect(ui->connect_btn, SIGNAL(clicked()), this, SLOT(connectDevice()));
    connect(ui->disconnect_btn, SIGNAL(clicked()), this, SLOT(disconnectDevice()));
    connect(ui->devices_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseDevice(int)));
    connect(ui->baudrates_cb, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseBaudrate(int)));

    connect(bt_discovery, SIGNAL(finished()), this, SLOT(onDiscoveryFinished()));
    */
    
}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}
void DeviceConfiguration::refreshDevices()
{

}



void DeviceConfiguration::connectDevice()
{

}

void DeviceConfiguration::disconnectDevice()
{

}

void DeviceConfiguration::chooseDevice(int id)
{
   
}

void DeviceConfiguration::chooseBaudrate(int id)
{
    qDebug() << "[DeviceConfiguration] choosed baudrate[" << id
             <<  "]" ; //<< devices[id];
}

void DeviceConfiguration::onDiscoveryFinished()
{

}
