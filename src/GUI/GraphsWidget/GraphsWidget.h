#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include "GraphsWidget.h"

namespace Ui {
class GraphsWidget;
}

class GraphsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphsWidget(QWidget *parent = nullptr);
    ~GraphsWidget();

private:
    Ui::GraphsWidget *ui;

};

#endif // MONITORWIDGET_H
