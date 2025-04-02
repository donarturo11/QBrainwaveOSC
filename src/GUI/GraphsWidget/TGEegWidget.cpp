#include "TGEegWidget.h"

TGEegWidget::TGEegWidget(QWidget *parent) 
: TGWidget(parent)
{
    _series = new QBarSeries();
    _eegValues = new QBarSet("Eeg");
    _axisX = (QValueAxis*) new QBarCategoryAxis();
    _axisY = new QValueAxis();
    init();
}

TGEegWidget::~TGEegWidget()
{
    delete _axisY;
    delete _axisX;
    delete _eegValues;
}

void TGEegWidget::setupAxes()
{
    _chart->addAxis(_axisX, Qt::AlignBottom);
    series()->attachAxis(_axisX);
    _axisY->setRange(0,100);

    _chart->addAxis(_axisY, Qt::AlignLeft);
    _series->attachAxis(_axisY);
}


void TGEegWidget::setupGui()
{
    _label->setGeometry(0, 40, 100, 40);
    _chartview->setGeometry(100,0,500,180);
    series()->setBarWidth(0.9);
    setupLabels();
    setupFonts();
}

void TGEegWidget::initValues()
{
    for (int i=0; i<8; i++) {
        *_eegValues << 0;
    }
    series()->append(_eegValues);
}

void TGEegWidget::setupLabels()
{
    QStringList categories;
    categories << QString::fromUtf8("&delta")
               << QString::fromUtf8("&theta")
               << QString::fromUtf8("Lo &alpha")
               << QString::fromUtf8("Hi &alpha")
               << QString::fromUtf8("Lo &beta")
               << QString::fromUtf8("Hi &beta")
               << QString::fromUtf8("Lo &gamma")
               << QString::fromUtf8("Hi &gamma");
    reinterpret_cast<QBarCategoryAxis*>(_axisX)->append(categories);
}

void TGEegWidget::setupFonts()
{
    QFont labelsFont;
    labelsFont.setPixelSize(13);
    _axisX->setLabelsFont(labelsFont);
    _axisY->setLabelsFont(labelsFont);
}

void TGEegWidget::setValues(float* eeg)
{
    for (int i=0; i<8; i++) {
        _eegValues->replace(i, (double)(eeg[i])*100);
    }
    update();
}


