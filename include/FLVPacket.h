#pragma once

#include <string>
#include <bitset>

#include <stdint.h>

#include "FLVHeader.h"

// note that all 2 byte or more numbers, in an flv packet / header, are stored using Big Endian.

enum FLVPacketType {
        PACKET_TYPE_AUDIO = 8,
        PACKET_TYPE_VIDEO = 9,
        PACKET_TYPE_META_DATA = 18,
};

class FLVPacket {
public:
    FLVPacket(void *data, std::bitset<24> dataSize, uint32_t previousPacketSize, uint32_t timestamp, uint8_t streamID, FLVPacketType packetType);
    ~FLVPacket();

    std::string getPacketContent();
private:
    uint32_t previousPacketSize; // first packet of the stream should have a previous packet size of 0.
    FLVPacketType packetType;
    std::bitset<24> packetDataSize;
    std::bitset<24> timestampLower;
    uint8_t timestampUpper;
    uint8_t streamID;
    std::bitset<24> dataSize;

    void *data;

};
