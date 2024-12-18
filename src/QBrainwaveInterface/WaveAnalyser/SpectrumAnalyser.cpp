#include "SpectrumAnalyser.h"
#include <algorithm>
#include <complex>
#ifdef USE_KISSFFT
#include "kissfft.hh"
#else
#include <fftw3.h>
#endif
namespace Brainwave {
SpectrumAnalyser::SpectrumAnalyser(float samplerate, float freq_resolution)
: _samplerate(samplerate)
, _freq_resolution(freq_resolution)
{}

SpectrumAnalyser::~SpectrumAnalyser()
{}

void SpectrumAnalyser::analyse(std::vector<float>& signal)
{
    size_t nfft = (_samplerate/_freq_resolution);
    if (_spectrogram.size() != nfft)
        _spectrogram.resize(nfft);
    std::vector<std::complex<double>> fft_out(nfft+1);
    if(signal.size() < nfft) signal.resize(nfft);
    auto hanning = [nfft](size_t n) -> double {
        return 0.5 * (1.0 - std::cos(2.0 * M_PI * n / (nfft - 1)));
    };
    std::vector<double> in(nfft);
    for (int i=0; i<nfft; i++) {
        in[i] = signal[i] * hanning(i);
    }
    #ifdef USE_KISSFFT
    #pragma warning("Building with kissfft")
    kissfft<double> fft(nfft, false);
    fft.transform_real(in.data(), fft_out.data());
    #else
    #pragma warning("Building with fftw3")
    fftw_complex* out = reinterpret_cast<fftw_complex*>(fft_out.data());
    fftw_plan plan = fftw_plan_dft_r2c_1d(nfft, in.data(), out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    #endif
    // put to spectogram
    float freq = 0;
    for (size_t i = 0; i < nfft; i++) {
        freq = i * _freq_resolution;
        float mag = std::norm(fft_out[i]);
        _spectrogram[i] = mag;
    }
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
    for (size_t i = 0; i < _spectrogram.size(); ++i) {
        float freq = i * _freq_resolution;
        if (freq >= low_freq && freq <= high_freq) {
            power += _spectrogram[i];
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
