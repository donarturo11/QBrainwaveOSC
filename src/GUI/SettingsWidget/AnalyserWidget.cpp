#include "MainWindow.h"
#include "AnalyserWidget.h"
#include "ui_AnalyserWidget.h"

AnalyserWidget::AnalyserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyserWidget) /*, _settings(nullptr) */
{
    ui->setupUi(this);
    init();
}

AnalyserWidget::~AnalyserWidget()
{
   // if(_settings) delete _settings;
    delete ui;
}

void AnalyserWidget::init()
{
    connect(ui->enable_rawwave_analyser, SIGNAL(stateChanged(int)),
            this, SLOT(onRawWaveStateChanged(int)));
    onRawWaveStateChanged(ui->enable_rawwave_analyser->checkState());
    initSampleratesList();
}

void AnalyserWidget::initSampleratesList()
{
	QList<qint32> samplerates = { 256, 512  };
    ui->samplerate_cb->clear();
    for (auto s : samplerates) {
      ui->samplerate_cb->addItem(QString::number(s), s);
    }
    auto brainwave = MainWindow::mainWindow()->brainwaveInterface();
    auto analyser = brainwave->analyser();
    auto currentSamplerate = analyser->samplerate();
    auto cur_idx = ui->samplerate_cb->findData(currentSamplerate);
    ui->samplerate_cb->setCurrentIndex(cur_idx);
    connect(ui->samplerate_cb, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSamplerateChanged(int)));
}

void AnalyserWidget::onSamplerateChanged(int i)
{
	auto analyser = MainWindow::mainWindow()->brainwaveInterface()->analyser();
	auto samplerate = ui->samplerate_cb->itemData(i).toInt();
    analyser->setSamplerate(samplerate);
}

void AnalyserWidget::refresh()
{
    
}

void AnalyserWidget::onRawWaveStateChanged(int state)
{
    auto brainwave = MainWindow::mainWindow()->brainwaveInterface();
    if (state) 
        brainwave->onRawWaveAnalyserEnabled();
    else
        brainwave->onRawWaveAnalyserDisabled();
}

void AnalyserWidget::onParametersQuery()
{
    //if (!_settings) return;
    //QVariantMap p(_settings->getParameters());
    //emit parametersSent(p);
}
