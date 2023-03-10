#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H
#include <QObject>
#include <QtCore>

class BluetoothManager : public QObject
{
    Q_OBJECT
public:
    BluetoothManager(QObject *parent = nullptr);
    ~BluetoothManager();
    void printPtr();
    static const BluetoothManager* bluetoothManager(){ return currentInstance; };
protected:
    static BluetoothManager* currentInstance;
};

#endif // BLUETOOTHMANAGER_H
