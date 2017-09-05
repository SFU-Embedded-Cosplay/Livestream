#include "FLVPacket.h"


FLVPacket::FLVPacket(
    void *data,
    std::bitset<24> dataSize,
    uint32_t previousPacketSize,
    uint32_t timestamp,
    uint8_t streamID,
    FLVPacketType packetType
) : data(data),
    dataSize(dataSize),
    previousPacketSize(previousPacketSize),
    timestampLower(timestamp & 0xfff),
    timestampUpper(timestamp >> 24),
    streamID(streamID),
    packetType(packetType)
{

}

FLVPacket::~FLVPacket() {

}

std::string FLVPacket::getPacketContent() {
    return "";
}
