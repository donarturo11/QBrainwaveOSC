#include "SpectrumAnalyser.h"
#include <iostream>
#include <iomanip>
namespace Brainwave {
SpectrumAnalyser::SpectrumAnalyser(float samplerate, float freq_resolution)
: _samplerate(samplerate)
, _freq_resolution(2)
, _fft_out(_samplerate/_freq_resolution)
{}

SpectrumAnalyser::~SpectrumAnalyser()
{}

void SpectrumAnalyser::analyse(std::vector<float>& signal)
{
    size_t nfft = _fft_out.size();
    kissfft<float> fft(nfft, false);
    fft.transform_real(signal.data(), _fft_out.data());
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
    for (size_t i = 0; i < _fft_out.size(); ++i) {
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
