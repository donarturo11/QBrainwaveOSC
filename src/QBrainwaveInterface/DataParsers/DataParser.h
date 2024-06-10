#ifndef BRAINWAVE_DATAPARSER
#define BRAINWAVE_DATAPARSER
#include "DataHandler.h"
namespace Brainwave {
class DataParser
{
public:
    DataParser(DataHandler *handler = nullptr) : _handler(handler) {}
    virtual ~DataParser(){
        _handler = nullptr;
        }
    virtual void parseByte(unsigned char c) = 0;
    void parseBytes(const char *buffer, unsigned int size) {
        for (int i = 0; i<size; i++) {
            parseByte(buffer[i]);
        }
    }
    void setDataHandler(DataHandler *handler){ _handler = handler; }
    DataHandler *datahandler() { return _handler; }
protected:
    DataHandler *_handler;
};
}
#endif
