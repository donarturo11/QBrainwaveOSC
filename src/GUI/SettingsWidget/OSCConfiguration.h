#ifndef OSCCONFIGURATION_H
#define OSCCONFIGURATION_H

#include <QWidget>
namespace Ui {
class OSCConfiguration;
}

class OSCConfiguration : public QWidget
{
    Q_OBJECT
    
public:
    explicit OSCConfiguration(QWidget *parent = nullptr);
    ~OSCConfiguration();
public slots:
    
public slots:
    
private:
    Ui::OSCConfiguration *ui;
    
protected:
    
};

#endif // OSCCONFIGURATION_H
