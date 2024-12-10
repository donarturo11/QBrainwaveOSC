#ifndef BRAINWAVE_DATAHANDLER_H
#define BRAINWAVE_DATAHANDLER_H
#include "EegBands.h"
namespace Brainwave {
class DataHandler
{
    bool _raw_wave_analyser = true;
public:
    virtual void onRaw(float) = 0;
    virtual void onEeg(EegBands) = 0;
    virtual void onAttention(float) = 0;
    virtual void onMeditation(float) = 0;
    virtual void onBlinkStrength(float) = 0;
    virtual void onPoorSignal(float) = 0;
    virtual void onBattery(float) = 0;
    void enableRawWaveAnalyser(){ _raw_wave_analyser = true; }
    void disableRawWaveAnalyser(){ _raw_wave_analyser = false; }
    bool rawWaveAnalyserEnabled() const { return _raw_wave_analyser; }
};

} // namespace Brainwave
#endif
