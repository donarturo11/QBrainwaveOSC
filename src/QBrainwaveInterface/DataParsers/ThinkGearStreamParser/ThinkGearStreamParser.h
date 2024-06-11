#ifndef BRAINWAVE_THINKGEARSTREAMPARSER
#define BRAINWAVE_THINKGEARSTREAMPARSER
#include "DataParser.h"
#include <vector>
#include <memory>
#include "ThinkGearPayload.h"
#include "ThinkGearCodes.h"
#include "ThinkGearDataHandler.h"
namespace Brainwave {
class ThinkGearStreamParser : public DataParser
{
    ThinkGear::ThinkGearDataHandler handleDataValue;
public:
    ThinkGearStreamParser(DataHandler *handler = nullptr);
    ~ThinkGearStreamParser();
    void parseByte(unsigned char c);
private:
    void receiveSyncByte();
    void reset();
    void initPayload();
    void writePayload();
    void checkPayload();
    void parsePayload();
protected:
    unsigned char _last_byte;
    Brainwave::ParserStatus _status;
    Brainwave::ReceiveStatus _receive_status;
    std::unique_ptr<ThinkGear::ThinkGearPayload> _payload;
};
}
#endif
