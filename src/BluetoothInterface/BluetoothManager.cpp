#include "BluetoothManager.h"

BluetoothManager* BluetoothManager::currentInstance;

BluetoothManager::BluetoothManager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "BluetoothManager c-tor";
    BluetoothManager::currentInstance = this;
}

BluetoothManager::~BluetoothManager()
{
    //if(currentInstance) delete currentInstance;
}

void BluetoothManager::printPtr()
{
    qDebug() << this;
}

