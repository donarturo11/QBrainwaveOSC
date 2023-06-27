#include "OSCConfiguration.h"
#include "ui_OSCConfiguration.h"
#include "MainWindow.h"
#include <QVector>

OSCConfiguration::OSCConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OSCConfiguration)
{
    ui->setupUi(this);
    connect(ui->host_edit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));
    connect(ui->port_chooser, SIGNAL(valueChanged(int)), this, SLOT(onOscOptionChanged(int)));
    connect(ui->raw_toggle, SIGNAL(stateChanged(int)), this, SLOT(onOscOptionChanged(int)));
    connect(ui->eeg_toggle, SIGNAL(stateChanged(int)), this, SLOT(onOscOptionChanged(int)));
    connect(ui->attmed_toggle, SIGNAL(stateChanged(int)), this, SLOT(onOscOptionChanged(int)));
    connect(ui->signal_toggle, SIGNAL(stateChanged(int)), this, SLOT(onOscOptionChanged(int)));
    connect(ui->osc_enable_toggle, SIGNAL(stateChanged(int)), this, SLOT(onOscEnabledStateChanged(int)));
    osc = MainWindow::mainWindow()->oscSender();
    updateFlags();
}

OSCConfiguration::~OSCConfiguration()
{
    delete ui;
}

void OSCConfiguration::onEditingFinished()
{
    QString addr(ui->host_edit->text());
    osc->setAddress(addr);
}

void OSCConfiguration::onAddressChanged(QString address)
{
    qDebug() << __PRETTY_FUNCTION__ << "";    
}

void OSCConfiguration::onPortChanged(int port)
{
    qDebug() << __PRETTY_FUNCTION__ << ":" << port;
    osc->setPort((short) port);
}

void OSCConfiguration::onOscOptionChanged(int state)
{
    updateFlags();
}

void OSCConfiguration::updateFlags()
{
    int flags=0;
    if (ui->raw_toggle->checkState()) flags |= OSCSENDER_ENABLE_RAW;
    if (ui->eeg_toggle->checkState()) flags |= OSCSENDER_ENABLE_EEG;
    if (ui->attmed_toggle->checkState()) flags |= OSCSENDER_ENABLE_ATTENTION;
    if (ui->signal_toggle->checkState()) flags |= OSCSENDER_ENABLE_SIGNAL;
    osc->setFlags(flags);
}

void OSCConfiguration::onOscEnabledStateChanged(int state)
{
    if (state) osc->connectListener();
    else osc->disconnectListener();
}

