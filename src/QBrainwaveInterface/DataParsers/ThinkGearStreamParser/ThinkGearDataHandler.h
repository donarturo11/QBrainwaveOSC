#ifndef THINKGEARDATAVALUEHANDLER_H
#define THINKGEARDATAVALUEHANDLER_H
#include <vector>
#include "DataHandler.h"
namespace Brainwave {
namespace ThinkGear {
class ThinkGearDataHandler
{
public:    
    ThinkGearDataHandler(Brainwave::DataHandler*);
    ~ThinkGearDataHandler();
    void operator()(unsigned char excode, unsigned char code, std::vector<unsigned char> value);
private:
    void onRaw(short);
    void onBattery(unsigned char);
    void onPoorSignal(unsigned char);
    void onAttention(unsigned char);
    void onMeditation(unsigned char);
    void onEeg(std::vector<unsigned char>);
protected:
    Brainwave::DataHandler* _handler;
};
} // namespace ThinkGear
} // namespace Brainwave
#endif
