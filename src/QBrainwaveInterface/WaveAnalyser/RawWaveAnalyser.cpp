#include "RawWaveAnalyser.h"
#include <iostream>
namespace Brainwave {
RawWaveAnalyser::RawWaveAnalyser(int bufsize, float samplerate, DataHandler *handler)
: _handler(handler)
, _wave_buf(bufsize)
, _samplerate(samplerate)
, _sp(samplerate)
{}

RawWaveAnalyser::~RawWaveAnalyser()
{}

void RawWaveAnalyser::put(float& value)
{
    _wave_buf.put(value);
    if (_wave_buf.full()) process();
}

void RawWaveAnalyser::process()
{
    auto input = _wave_buf.readAll();
    auto eeg   = doSpectrumAnalysis(input);
    
    // compute band powers sums
    float theta = eeg.theta;
    float alpha = eeg.lowAlpha + eeg.highAlpha;
    float beta = eeg.lowBeta + eeg.highBeta;
    
    float norm_total = theta + alpha + beta;
    alpha /= norm_total;
    beta  /= norm_total;
    theta /= norm_total;
    
    // notify eeg, meditation, attention
    _handler->onEeg(eeg);
    
    // see: https://doi.org/10.1016/j.ijpsycho.2024.112465
    _handler->onMeditation(theta + alpha);
    _handler->onAttention(beta);
}

EegBands RawWaveAnalyser::doSpectrumAnalysis(std::vector<float>& in)
{
    _sp.analyse(in);
    return _sp.getEegPowers();
}

}
