#include "RawWaveAnalyser.h"
#include <iostream>
namespace Brainwave {
RawWaveAnalyser::RawWaveAnalyser(int bufsize, DataHandler *handler) :
_buffersize(bufsize), _handler(handler)
{
    std::cout << "RawWaveAnalyser c-tor" << std::endl;
}

RawWaveAnalyser::~RawWaveAnalyser()
{
    std::cout << "RawWaveAnalyser d-tor" << std::endl;
}

void RawWaveAnalyser::push_back(float value)
{
    _wave.push_back(value);
    if (_wave.size() == _buffersize) process();
}

void RawWaveAnalyser::process()
{
    std::cout << "RawWaveAnalyser:" << std::endl;
    std::cout << "Wave num elements: ";
    std::cout << _wave.size();
    std::cout << std::endl;
    _wave.clear();
}

}
