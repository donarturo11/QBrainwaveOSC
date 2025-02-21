#include "ThinkGearDataHandler.h"
#include "ThinkGearCodes.h"
#include "EegBands.h"
#include <iostream>
#include <iomanip>
namespace Brainwave {
namespace ThinkGear {
ThinkGearDataHandler::ThinkGearDataHandler(Brainwave::DataHandler* handler)
 : _handler(handler)
{}

ThinkGearDataHandler::~ThinkGearDataHandler()
{}

void ThinkGearDataHandler::operator()
                ( unsigned char excode,
                  unsigned char code,
                  std::vector<unsigned char> value
                )
{
    switch (code) {
        case(ThinkGearCodes::PoorSignal): onPoorSignal(value[0]); break;
        case(ThinkGearCodes::Attention): onAttention(value[0]); break;
        case(ThinkGearCodes::Meditation): onMeditation(value[0]); break;
        case(ThinkGearCodes::RawSignal): onRaw((value[0] << 8) | value[1]); break;
        case(ThinkGearCodes::Battery): onBattery(value[0]); break;
        case(ThinkGearCodes::AsicEegPowerInt): onEeg(value); break;
        default: std::cerr << "undefined code: "
                 << std::hex << std::setw(2) << std::setfill('0')
                 << (int) code
                 << std::endl;
    }
}                

void ThinkGearDataHandler::onRaw(short v)
{
    _handler->onRaw( ((float) v / 2048) );
}

void ThinkGearDataHandler::onBattery(unsigned char v)
{
    _handler->onBattery( ((float) v / 127) );
}

void ThinkGearDataHandler::onPoorSignal(unsigned char v)
{
    if (_handler->rawWaveAnalyserEnabled()) return;
    _handler->onPoorSignal( ((float) v / 255) );
}

void ThinkGearDataHandler::onAttention(unsigned char v)
{
    if (_handler->rawWaveAnalyserEnabled()) return;
    _handler->onAttention( ((float) v / 100) );
}

void ThinkGearDataHandler::onMeditation(unsigned char v)
{
    if (_handler->rawWaveAnalyserEnabled()) return;
    _handler->onMeditation( ((float) v / 100) );
}

void ThinkGearDataHandler::onEeg(std::vector<unsigned char> bytes)
{
    if (_handler->rawWaveAnalyserEnabled()) return;
    int eegSum = 0;
    EegBands eeg;
    std::vector<int> eegValues;
    std::vector<unsigned char>::iterator b = bytes.begin();
    while (b != bytes.end()) {
        int val = 0;
        val |= (*b++) << 16;
        val |= (*b++) << 8;
        val = (*b++);
        eegSum += val;
        eegValues.push_back(val);
    }
    auto val = eegValues.begin();
    for (float *e = &(eeg.delta); e != (&(eeg.highGamma)+1); e++)
    {
        *e = (*(val++) * 1.00) / eegSum;
    }
    _handler->onEeg(eeg);
}



} // namespace ThinkGear
} // namespace Brainwave
