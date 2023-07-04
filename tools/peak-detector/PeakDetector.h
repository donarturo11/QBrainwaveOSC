#ifndef PEAK_DETECTOR
#define PEAK_DETECTOR
#include <vector>
class PeakDetector
{
public:
    PeakDetector();
    ~PeakDetector();
    static int maxCount;
    void inputValue(short val);
private:
    void resetCounter();
    void countMediana();
    void onPeakDetected(short val);
protected:
    short _average_min;
    short _average_max;
    short _mediana;
    int _counter;
    std::vector<short> _values;
    bool _detecting;
};


#endif
