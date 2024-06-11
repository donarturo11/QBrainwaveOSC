#include "ThinkGearStreamParser.h"
#include <iostream>
#include <iomanip>
namespace Brainwave {
using namespace Brainwave;    
using namespace ThinkGear;
ThinkGearStreamParser::ThinkGearStreamParser(DataHandler *handler)
    : DataParser(handler), handleDataValue(ThinkGearDataHandler(handler))
{
    std::cout << "ThinkGearStreamParser c-tor" << std::endl;
    _status = ParserStatus::Idle;
}

ThinkGearStreamParser::~ThinkGearStreamParser()
{
    std::cout << "ThinkGearStreamParser d-tor" << std::endl;
}

void ThinkGearStreamParser::parseByte(unsigned char c)
{
    _last_byte = c;
    switch (_status) {
        case( ParserStatus::Idle ): receiveSyncByte(); break;
        case( ParserStatus::Sync ): receiveSyncByte(); break;
        case( ParserStatus::PayloadLength ): initPayload(); break;
        case( ParserStatus::Payload ): writePayload(); break;
        case( ParserStatus::Checksum ): checkPayload(); break;
        default: _receive_status = ReceiveStatus::Unrecognized;
    }
}


void ThinkGearStreamParser::receiveSyncByte()
{
    //using namespace Brainwave;
    if (_last_byte != ThinkGearCodes::SyncByte) {
        reset();
        return;
    }
    
    switch (_status) { 
        case ( ParserStatus::Idle ): _status = ParserStatus::Sync; break;
        case ( ParserStatus::Sync ): _status = ParserStatus::PayloadLength; break;
        default: reset(); return;
    }
}

void ThinkGearStreamParser::reset()
{
    _payload.release();
    _status = ParserStatus::Idle;
}

void ThinkGearStreamParser::initPayload()
{ 
    //using namespace Brainwave;
    if (_last_byte > ThinkGearCodes::SyncByte) {
        _receive_status = ReceiveStatus::PlenghtTooLarge;
        reset();
        return;
    } else if (_last_byte == ThinkGearCodes::SyncByte) {
        _receive_status = ReceiveStatus::InvalidWithSync;
        reset();
        return;
    }
    _payload = std::make_unique<ThinkGearPayload>(_last_byte);
    _status = ParserStatus::Payload;
    
}

void ThinkGearStreamParser::writePayload()
{
    _payload->writeByte(_last_byte);
    if (_payload->completed()) _status = ParserStatus::Checksum;
}

void ThinkGearStreamParser::checkPayload()
{
    _payload->setChecksum(_last_byte);
    if (_payload->isValid()) {
        _receive_status = ReceiveStatus::Success;
        parsePayload();
    } else {
        _receive_status = ReceiveStatus::ChecksumFailed;
    }
    reset();
}

void ThinkGearStreamParser::parsePayload()
{
    auto payload = _payload->toVector();
    std::vector<unsigned char>::iterator it = payload.begin();
    
    while (it != payload.end()) {
        unsigned char extendedCodeLevel = 0;
        unsigned char code = 0;
        unsigned char numBytes = 0;
        while (*it == ThinkGearCodes::ExcodeByte) {
            extendedCodeLevel++;
            it++;
        }
        code = *(it++);
        numBytes = (code & 0x80) ? *(it++) : 1;
        std::vector<unsigned char> value(it, (it+numBytes));
        handleDataValue(extendedCodeLevel, code, value);
        it += numBytes;
    }
    reset();
}
   
}
