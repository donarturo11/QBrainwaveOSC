#ifndef BRAINWAVE_TWOBYTERAWPARSER
#define BRAINWAVE_TWOBYTERAWPARSER
#include "DataParser.h"
namespace Brainwave {
class TwoByteRawParser : public DataParser
{
public:
    TwoByteRawParser(DataHandler *handler = nullptr);
    ~TwoByteRawParser();
    void parseByte(unsigned char c);
protected:
    short _value;
};
}
#endif
