#ifndef BRAINWAVE_RAWWAVEANALYSER
#define BRAINWAVE_RAWWAVEANALYSER
#include "DataHandler.h"
#include <vector>
namespace Brainwave {
class RawWaveAnalyser
{
public:
    RawWaveAnalyser(int bufsize, DataHandler *handler);
    ~RawWaveAnalyser();
    void push_back(float value);
    void setBufferSize(int b) {_buffersize = b;}
    int buffersize() const { return _buffersize; }
    void setSamplerate(int s) { _samplerate = s; }
    int samplerate() const { return _samplerate; }
    void setDataHandler(DataHandler *h) { _handler = h; }
    DataHandler *handler() const { return _handler; }
private:
    void process();
    DataHandler *_handler;
    int _buffersize;
    int _samplerate;
    std::vector<float> _wave;
};
}
#endif
