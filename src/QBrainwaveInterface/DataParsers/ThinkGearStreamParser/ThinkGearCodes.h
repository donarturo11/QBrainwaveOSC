#ifndef THINKGEARCODES_H
#define THINKGEARCODES_H
namespace Brainwave {
namespace ThinkGear {
typedef enum {
    Battery=0x01,
    PoorSignal,
    HeartRate,
    Attention,
    Meditation,
    Raw8Bit,
    RawMarker,
    RawSignal=0x80,
    EegPowers,
    AsicEegPowerInt=0x83,
    SyncByte=0xAA,
    ExcodeByte=0x55
} ThinkGearCodes;
} // namespace ThinkGear
} // namespace Brainwave
#endif
