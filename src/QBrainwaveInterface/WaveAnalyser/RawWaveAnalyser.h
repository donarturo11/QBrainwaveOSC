#ifndef BRAINWAVE_RAWWAVEANALYSER
#define BRAINWAVE_RAWWAVEANALYSER
#include "DataHandler.h"
#include "KISSRingBuffer.h"
#include "SpectrumAnalyser.h"
#include <vector>
namespace Brainwave {
class RawWaveAnalyser
{
public:
    RawWaveAnalyser(int bufsize, float samplerate, DataHandler *handler);
    ~RawWaveAnalyser();
    void put(float& value);
    void setBufferSize(int b) {_wave_buf.resize(b);}
    size_t buffersize() const { return _wave_buf.capacity(); }
    void setSamplerate(int s) { _samplerate = s; }
    int samplerate() const { return _samplerate; }
    void setDataHandler(DataHandler *h) { _handler = h; }
    DataHandler *handler() const { return _handler; }
private:
    void process();
    EegBands doSpectrumAnalysis(std::vector<float>&);
    DataHandler *_handler;
    int _samplerate;
    SpectrumAnalyser _sp;
    KISSRingBuffer<float> _wave_buf;
};
}
#endif
