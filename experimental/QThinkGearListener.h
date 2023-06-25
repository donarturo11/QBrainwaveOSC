#ifndef QTHINKGEARLISTENER_H
#define QTHINKGEARLISTENER_H
#include <QObject>

class QThinkGearListener
{
public:
    virtual void onThinkGearRaw(short val) = 0;
    virtual void onThinkGearBattery(unsigned char val) = 0;
    virtual void onThinkGearPoorSignal(unsigned char val) = 0;
    virtual void onThinkGearAttention(unsigned char val) = 0;
    virtual void onThinkGearMeditation(unsigned char val) = 0;
    virtual void onThinkGearEeg(EegValues val) = 0;
    virtual void onThinkGearConnecting(unsigned char val) = 0;
    virtual void onThinkGearReady(unsigned char val) = 0;
    virtual void onThinkGearError(unsigned char val) = 0;
    virtual void onThinkGearBlinkStrength(unsigned char val) = 0;
};
/*
class QThinkGearDebugListener : public QThinkGearListener
{
    Q_OBJECT
public:
    QThinkGearDebugListener(QObject *parent=0) : QThinkGearListener(parent){}
public slots:
    void onThinkGearRaw(short val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearBattery(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearPoorSignal(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearAttention(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearMeditation(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearEeg(EegValues val)
    { 
        qDebug() << __FUNCTION__;
        for (auto v : val.getAllValues()) {
            qDebug() << QString::fromStdString(v.key()) << ":" << QString::number(v.value());
        } 
    }
    void onThinkGearConnecting(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearReady(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearError(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
    void onThinkGearBlinkStrength(unsigned char val) { qDebug() << __FUNCTION__ << " " << val; }
};
*/

class QThinkGearWidget : public QWidget, private QThinkGearListener 
{
    Q_OBJECT
public:
QThinkGearWidget(QWidget *parent) : QWidget(parent){}
//Q_OBJECT
//public:
//    QThinkGearWidget(QObject *parent=0) : QObject(parent){}
};
 

#endif // QTHINKGEARLISTENER_H
