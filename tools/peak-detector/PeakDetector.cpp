#include "PeakDetector.h"
#include <iostream>

int PeakDetector::maxCount = 512;
PeakDetector::PeakDetector()
{
    _detecting = false;
}

PeakDetector::~PeakDetector()
{

}

void PeakDetector::inputValue(short val)
{
    _values.push_back(val);
    _counter++;
    if ((val > (_average_max+2*_mediana)) || (val < (_average_min-2*_mediana))) {
        onPeakDetected(val);
        _detecting = false;
    }
    else {
        _detecting = true;
    }
    if (_counter>maxCount) {
        countMediana();
        resetCounter();
    }
}

void PeakDetector::onPeakDetected(short val)
{
    if (!_detecting) return;
    std::cout << "Detected peak: " << val << std::endl;
    //resetCounter();
}

void PeakDetector::countMediana()
{
    int sum=0;
    int max_sum=0;
    int max_count=0;
    
    int min_sum=0;
    int min_count=0;
    
    _average_max=0;
    _average_min=0;
    for (short v : _values) {
        sum+=v;
        if (v > _average_max) {
            max_sum += v;
            max_count++;
        }
        if (v < _average_min) {
            min_sum += v;
            min_count++;
        }
    }
    _average_max = (max_sum / max_count)*2;
    _average_min = (min_sum / min_count)*2;
    _mediana = sum / maxCount;
    
    std::cout << "=======================" << std::endl;
    std::cout << "Average max: " << _average_max << std::endl;
    std::cout << "Mediana: " << _mediana << std::endl;
    std::cout << "Average min: " << _average_min << std::endl;
    std::cout << "=======================" << std::endl;
    _values.clear();
    if (!_detecting) _detecting = true;
}

void PeakDetector::resetCounter()
{
    _counter = 0;
    //_maxima = 0;
    //_minima = 0;
}

