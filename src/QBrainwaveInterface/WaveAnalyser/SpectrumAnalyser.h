#ifndef BRAINWAVE_SPECTRUMANALYSER
#define BRAINWAVE_SPECTRUMANALYSER
#include "EegBands.h"
#include <vector>
namespace Brainwave {
class SpectrumAnalyser
{
    float _freq_resolution;
    float _samplerate;
    std::vector<float> _spectrogram;
    unsigned int _nSamples;
public:
    SpectrumAnalyser(float, float freq_resolution = 1.0);
    ~SpectrumAnalyser();
    void analyse(std::vector<float>&);
    EegBands getEegPowers();
    float    getBandPower(float, float);
    void normalizeEeg(EegBands*);
private:
    
};
}
#endif
