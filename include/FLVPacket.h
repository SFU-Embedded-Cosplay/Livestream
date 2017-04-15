#pragma once

#include <string>
#include <bitset>

#include <stdint.h>

#include "FLVHeader.h"

// note that all 2 byte or more numbers, in an flv packet / header, are stored using Big Endian.

class FLVPacket {
public:
    FLVPacket();
    ~FLVPacket();

    uint32_t previousPacketSize; // first packet of the stream should have a previous packet size of 0.
    uint8_t packetType;
    std::bitset<24> packetDataSize;
    std::bitset<24> timestampLower;
    uint8_t timestampUpper;
    uint8_t streamID;

    void *data;
private:

};
