#include "TwoByteRawParser.h"
#include <iostream>
namespace Brainwave {
TwoByteRawParser::TwoByteRawParser(DataHandler *handler)
    : DataParser(handler)
{
    std::cout << "TwoByteRawParser c-tor" << std::endl;
}

TwoByteRawParser::~TwoByteRawParser()
{
    std::cout << "TwoByteRawParser d-tor" << std::endl;
}

void TwoByteRawParser::parseByte(unsigned char c)
{
    if (c & 0x80) {
        _value = 0;
        _value |= (c&0x3f) << 6;
    } else if (c & 0x40) {
        _value |= c&0x3f;
        _handler->onRaw((float)((_value-2048)/2048.0000));
    }
}
    
}
