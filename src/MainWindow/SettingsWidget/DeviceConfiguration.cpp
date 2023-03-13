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
    connect(ui->refresh_btn, SIGNAL(clicked()),
            bt_manager, SLOT(refreshDevices()));
    connect(ui->connect_btn, SIGNAL(clicked()),
            bt_manager, SLOT(connectDevice()));
    connect(ui->disconnect_btn, SIGNAL(clicked()),
            bt_manager, SLOT(disconnectDevice()));
    connect(ui->devices_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseDevice(int)));
    connect(ui->baudrates_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseBaudrate(int)));
    connect(bt_manager, SIGNAL(deviceDiscoveryFinished()), this, SLOT(onDeviceDiscoveryFinished()));
    connect(bt_manager, SIGNAL(deviceDiscoveryUpdated(QBluetoothDeviceInfo)), this, SLOT(onDeviceDiscoveryUpdated(QBluetoothDeviceInfo)));
}

DeviceConfiguration::~DeviceConfiguration()
{
    delete ui;
}

void DeviceConfiguration::chooseDevice(int id)
{
    auto address = ui->devices_cb->currentData().toString();
    qDebug() << "Choose device" << address;
    bt_manager->setup(address);
}

void DeviceConfiguration::chooseBaudrate(int id)
{
    qDebug() << "[DeviceConfiguration] choosed baudrate[" << id
             <<  "]" ; //<< devices[id];
}

void DeviceConfiguration::onDeviceDiscoveryFinished()
{
    auto detected_devices = bt_manager->getDevicesList();
    auto devices_cb = ui->devices_cb;
    devices_cb->clear();
    for (auto dev : detected_devices) {
        QString itemText = dev.name() + " " + dev.address().toString();
        devices_cb->addItem(itemText, dev.address().toString() );
    }
    qDebug() << "Device discovery finished";
}

void DeviceConfiguration::onDeviceDiscoveryUpdated(QBluetoothDeviceInfo dev)
{
    qDebug() << "onDeviceDiscoveryUpdated";
    QString itemText = dev.name() + " " + dev.address().toString();
    qDebug() << "item to add: " << itemText;
    ui->devices_cb->addItem(itemText, dev.address().toString() );
}