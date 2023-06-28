#ifndef OSCMSG_H
#define OSCMSG_H
#include <string>
class OSCMessage
{
public:
    OSCMessage() {}
    OSCMessage(std::string path, std::string tag, int value) {
        _data="";
        append(path);
        append(tag);
        append((uint32_t) value);
    }
    std::string data() { return _data; }
    
private:
    void align() {
        int space = 4 - _data.size()%4;
        for (int i=0; i<space; i++) {
            _data += (unsigned char) 0x0;
        }
    }
    void append(std::string s) {
        _data += s;
        align();
    }
    void append(uint32_t val) {
        _data += (unsigned char) ((val >> 24) & 0xFF);
        _data += (unsigned char) ((val >> 16) & 0xFF);
        _data += (unsigned char) ((val >> 8) & 0xFF);
        _data += (unsigned char) ((val) & 0xFF);
    }
protected:
    std::string _data;
};

#endif // OSCMSG_H
