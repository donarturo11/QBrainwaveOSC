#ifndef BRAINWAVE_DATAHANDLER_H
#define BRAINWAVE_DATAHANDLER_H
#include "EegBands.h"
namespace Brainwave {
class DataHandler
{
public:
    virtual void onRaw(float) = 0;
    virtual void onEeg(EegBands) = 0;
    virtual void onAttention(float) = 0;
    virtual void onMeditation(float) = 0;
    virtual void onBlinkStrength(float) = 0;
    virtual void onPoorSignal(float) = 0;
    virtual void onBattery(float) = 0;
};

} // namespace Brainwave
#endif
