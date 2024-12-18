#include "SpectrumAnalyser.h"
#include <cmath>

namespace Brainwave {
SpectrumAnalyser::SpectrumAnalyser(float samplerate, float freq_resolution)
: _samplerate(samplerate)
, _freq_resolution(freq_resolution)
, _nfft(samplerate/freq_resolution)
#ifdef USE_KISSFFT
, _fft(_nfft, false)
#endif
{
    _fft_out.resize(_nfft+1);
    _input.resize(_nfft);
#ifdef USE_FFTW
    auto in = _input.data();
    auto out = reinterpret_cast<fftw_complex*>(_fft_out.data());
    _fftw_plan = fftw_plan_dft_r2c_1d(_nfft,
                                   in,
                                   out,
                                   FFTW_MEASURE);
#endif
}

SpectrumAnalyser::~SpectrumAnalyser()
{
    #ifdef USE_FFTW
    fftw_destroy_plan(_fftw_plan);
    #endif
}

void SpectrumAnalyser::analyse(std::vector<float>& signal)
{
    if(signal.size() < _nfft) signal.resize(_nfft);
    auto hanning = [&](size_t n) -> double {
        return 0.5 * (1.0 - std::cos(2.0 * M_PI * n / (_nfft - 1)));
    };
    for (int i=0; i<_nfft; i++) {
        _input[i] = signal[i] * hanning(i);
    }
    #ifdef USE_FFTW
    fftw_execute(_fftw_plan);
    #else
    fft.transform_real(_input.data(), _fft_out.data());
    #endif
}

EegBands SpectrumAnalyser::getEegPowers()
{
    EegBands eeg;
    /*
     *   See: https://developer.neurosky.com/docs/lib/exe/fetch.php?media=mindset_communications_protocol.pdf
     *   p. 8
     */
    eeg.delta     = getBandPower( 0.50f,  2.75f);
    eeg.theta     = getBandPower( 3.50f,  6.75f);
    eeg.lowAlpha  = getBandPower( 7.50f,  9.25f);
    eeg.highAlpha = getBandPower(10.00f, 11.75f);
    eeg.lowBeta   = getBandPower(13.00f, 16.75f);
    eeg.highBeta  = getBandPower(18.00f, 29.75f);
    eeg.lowGamma  = getBandPower(31.00f, 39.75f);
    eeg.highGamma = getBandPower(41.00f, 49.75f);
    normalizeEeg(&eeg);
    return eeg;
}

float SpectrumAnalyser::getBandPower(float low_freq, float high_freq)
{
    float power = 0.00f;
    size_t nPowers = 0;
    for (size_t i = 0; i < _nfft; ++i) {
        float freq = i * _freq_resolution;
        if (freq >= low_freq && freq <= high_freq) {
            power += std::norm(_fft_out[i]);
            nPowers++;
        }
    }
    return power/nPowers;
}

void SpectrumAnalyser::normalizeEeg(EegBands* eeg)
{
    float *eegVal = (float*)(eeg);
    size_t nElements = sizeof(EegBands)/sizeof(float);
    float total = 0;
    for (size_t i=0; i<nElements; i++) {
        total += eegVal[i];
    }
    for (size_t i=0; i<nElements; i++) {
        eegVal[i] = (total!=0) ? eegVal[i]/total : 0;
    }
}
    
}
