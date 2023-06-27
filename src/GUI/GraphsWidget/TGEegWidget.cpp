#include "TGEegWidget.h"

TGEegWidget::TGEegWidget(QString label, QWidget *parent) 
: TGWidget(label, parent)
{
    _series = new QBarSeries();
    _eegValues = new QBarSet("Eeg");
    _axisX = new QBarCategoryAxis();
    _axisY = new QValueAxis();
    init();
}

TGEegWidget::~TGEegWidget()
{
    delete _axisY;
    delete _axisX;
    delete _eegValues;
    delete _series;
}

void TGEegWidget::init()
{
    _label->setGeometry(0, 40, 100, 40);
    _chartview->setGeometry(100,0,500,180);
    series()->setBarWidth(0.9);
    _chart->addSeries(_series);

    initAxes();
    setupLabels();
    setupFonts();
    initValues();
}

void TGEegWidget::initAxes()
{
    _chart->addAxis(_axisX, Qt::AlignBottom);
    series()->attachAxis(_axisX);
    _axisY->setRange(0,100);

    _chart->addAxis(_axisY, Qt::AlignLeft);
    _series->attachAxis(_axisY);
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
    categories << QString::fromUtf8("\u03b8")     /* theta      */
               << QString::fromUtf8("\u03b4")     /* delta      */
               << QString::fromUtf8("Lo \u03b1")  /* low alpha  */
               << QString::fromUtf8("Hi \u03b1")  /* high alpha */
               << QString::fromUtf8("Lo \u03b2")  /* low beta   */
               << QString::fromUtf8("Hi \u03b2")  /* high beta  */
               << QString::fromUtf8("Lo \u03b3")  /* low gamma  */
               << QString::fromUtf8("Hi \u03b3"); /* high gamma */
    _axisX->append(categories);
}

void TGEegWidget::setupFonts()
{
    QFont labelsFont;
    labelsFont.setPixelSize(13);
    _axisX->setLabelsFont(labelsFont);
    _axisY->setLabelsFont(labelsFont);
}

void TGEegWidget::setValues(EegValues vals)
{
    for (int i=0; i<8; i++) {
        _eegValues->replace(i, (((double)vals[i].value()/(double)vals.sum())*100)  );
    }
    series()->append(_eegValues);
}


