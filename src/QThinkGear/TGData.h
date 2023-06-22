#ifndef TGDATA_H
#define TGDATA_H

#include <stdint.h>
#include <vector>
typedef struct _tgdata_t
{
    uint8_t code;
    uint8_t size;
    uint8_t value[64];
} tgdata_t;

class TGData
{
public:
    TGData(tgdata_t *d);
    TGData(unsigned char code, unsigned char size, const unsigned char *value);
    uint32_t toUInt32FromArray(uint8_t size, uint8_t *data);
    uint32_t toUInt32() { return toUInt32FromRow(0, 4); }
    short toShort() { return toUInt32FromRow(0, 2); }
    unsigned char toUChar() { return toUInt32FromRow(0, 1); }
    uint32_t toUInt32FromRow(uint8_t row_idx, uint8_t row_width);
    uint8_t* getRow(uint8_t row_idx, uint8_t row_width);
    std::vector<uint8_t> getStructItem(uint8_t item_idx, uint8_t* sizes);
    std::vector<uint32_t> deserializeArray(uint8_t capacity);
    int size() const { return _value.size(); }
    unsigned char code() const { return _code; }
    unsigned char* value() { return _value.data(); }
    tgdata_t TGData_c() const;
protected:
    uint8_t _code;
    std::vector<uint8_t> _value;
};
#endif // TGDATA_H
