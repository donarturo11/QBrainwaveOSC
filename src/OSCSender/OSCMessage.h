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
        size_t space = 4 - _data.size()%4;
        _data.append(space, (const char) 0x0);
    }
    void append(std::string &s) {
        _data.append(s);
        align();
    }
    void append(uint32_t val) {
        const char d[] = {
            (char)((val >> 24) & 0xFF),
            (char)((val >> 16) & 0xFF),
            (char)((val >> 8) & 0xFF),
            (char)((val) & 0xFF) 
        };
        _data.append(d, d+4);
    }
protected:
    std::string _data;
};

#endif // OSCMSG_H
