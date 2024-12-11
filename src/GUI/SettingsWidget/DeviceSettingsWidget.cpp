#include "MainWindow.h"
#include "DeviceSettingsWidget.h"
#include "ui_DeviceSettingsWidget.h"
#include "SerialPortSettings.h"
#include "DummyDeviceSettings.h"

struct PortInfo {
    QString name;
    DeviceSettings* (*create)(QWidget *widget);
};

const PortInfo ports[] = {
   // {"Dummy", &DummyDeviceSettings::create},
    {"Serial port", &SerialPortSettings::create}
};

DeviceSettingsWidget::DeviceSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceSettingsWidget),
    _settings(nullptr)
{
    ui->setupUi(this);
    init();
}

DeviceSettingsWidget::~DeviceSettingsWidget()
{
    if(_settings) delete _settings;
    delete ui;
}

void DeviceSettingsWidget::init()
{
    connect(ui->refresh_btn, SIGNAL(clicked()),
            this, SLOT(refresh()));
    connect(ui->ports_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(choosePort(int)));
    connect(ui->devices_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseDevice(int)));
    connect(ui->type_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseType(int)));
    connect(ui->baudrate_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chooseBaudrate(int)));
    connect(ui->enable_rawwave_analyser, SIGNAL(stateChanged(int)),
            this, SLOT(onRawWaveStateChanged(int)));
    initPorts();
}


void DeviceSettingsWidget::refresh()
{
    refreshDeviceCombobox();
    refreshBaudrateCombobox();
    refreshTypeCombobox();
}

void DeviceSettingsWidget::refreshDeviceCombobox()
{
    if (!_settings) return;
    auto devs = _settings->getDevicesList();
    ui->devices_cb->clear();
    for (auto d : devs) {
        ui->devices_cb->addItem(d, d);
    }
}

void DeviceSettingsWidget::refreshTypeCombobox()
{
    if (!_settings) return;
    auto devtypes = _settings->getDeviceTypes();
    ui->type_cb->clear();
    for (auto key : devtypes.keys()) {
        ui->type_cb->addItem(devtypes[key], key);
    }
}

void DeviceSettingsWidget::refreshBaudrateCombobox()
{
    if (!_settings) return;
    auto baudrates = _settings->getBaudrates();
    if (!baudrates.empty()) {
        ui->baudrate_label->show();
        ui->baudrate_cb->show();
        ui->baudrate_cb->clear();
        for (auto b : baudrates) {
            ui->baudrate_cb->addItem(QString::number(b), b);
        }
    } else {
        ui->baudrate_cb->clear();
        ui->baudrate_label->hide();
        ui->baudrate_cb->hide();
    }
}

void DeviceSettingsWidget::initPorts()
{
    ui->ports_cb->clear();
    for (auto p : ports) {
        ui->ports_cb->addItem(p.name, p.name);
    }
}

void DeviceSettingsWidget::choosePort(int id)
{
    if (_settings) delete _settings;
    if (ports[id].create) {
        _settings = ports[id].create(this);
        refresh();
    }
}

void DeviceSettingsWidget::chooseDevice(int id)
{
    if (!_settings) return;
    _settings->setPortname(ui->devices_cb->itemData(id).toString());
}

void DeviceSettingsWidget::chooseType(int id)
{
    if (!_settings) return;
    auto data = ui->type_cb->itemData(id);
    _settings->chooseType(data.toString());
}

void DeviceSettingsWidget::chooseBaudrate(int id)
{
    if (!_settings) return;
    emit baudrateChanged(ui->baudrate_cb->itemData(id).toInt());
}

void DeviceSettingsWidget::onRawWaveStateChanged(int state)
{
    auto brainwave = MainWindow::mainWindow()->brainwaveInterface();
    if (state) 
        brainwave->onRawWaveAnalyserEnabled();
    else
        brainwave->onRawWaveAnalyserDisabled();
}

void DeviceSettingsWidget::onParametersQuery()
{
    if (!_settings) return;
    QVariantMap p(_settings->getParameters());
    emit parametersSent(p);
}
