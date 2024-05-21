#ifndef BRAINWAVE_DATAPARSER
#define BRAINWAVE_DATAPARSER
namespace Brainwave {
class DataHandler
{
void *userData;
void (*handleData)(void *userData, void *args);
};

class DataParser
{
public:
    DataParser() {}
    DataParser(void *handler) {}
    virtual ~DataParser(){}
    virtual void init() = 0;
    virtual void parseByte(unsigned char c) = 0;
    void parseBytes(unsigned char *buffer, unsigned int size) {
        for (int i = 0; i<size; i++) {
            parseByte(buffer[i]);
        }
    }
    void setDataHandler(void *handler){ _handler = handler; }
    void *datahandler() { return _handler; }
protected:
    void *_handler;
};
}
#endif