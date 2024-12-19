#ifndef BRAINWAVE_SPECTRUMANALYSER
#define BRAINWAVE_SPECTRUMANALYSER
#include "EegBands.h"
#if defined(USE_FFTW)
#include <fftw3.h>
#elif defined(USE_KISSFFT)
#include "kissfft.hh"
#else

#endif
#include <algorithm>
#include <complex>
#include <vector>
namespace Brainwave {
class SpectrumAnalyser
{
    float _freq_resolution;
    float _samplerate;
    std::vector<double> _input;
    std::vector<std::complex<double>> _fft_out;
    std::size_t _nfft;
    #ifdef USE_FFTW
    fftw_plan _fftw_plan;
    #else
    kissfft<double> _fft;
    #endif
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
