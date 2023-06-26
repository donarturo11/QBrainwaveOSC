#ifndef TGEEG_WIDGET_H
#define TGEEG_WIDGET_H
#include "TGWidget.h"

class TGEegWidget : public TGWidget
{
    Q_OBJECT
public:
    TGEegWidget(QString label, QWidget *parent = nullptr);
    void init();
protected:
    
};

#endif // TGEEG_WIDGET_H
