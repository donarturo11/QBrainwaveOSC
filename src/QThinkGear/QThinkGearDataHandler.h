#ifndef QTHINKGEARDATAHANDLER_H
#define QTHINKGEARDATAHANDLER_H
#include <QObject>
#include <QtCore>
#include "TGData.h"

void QThinkGearDataHandle( unsigned char extendedCodeLevel,
                            unsigned char code,
                            unsigned char numBytes,
                            const unsigned char *value,
                            void *customData );
                            
class QThinkGearDataHandler : public QObject
{
    Q_OBJECT
public:
    QThinkGearDataHandler(QObject *parent = nullptr);
    ~QThinkGearDataHandler();
    void pushData(unsigned char extendedCodeLevel,
                  unsigned char code,
                  unsigned char numBytes,
                  const unsigned char *value);
};


#endif // QTHINKGEARDATAHANDLER_H
