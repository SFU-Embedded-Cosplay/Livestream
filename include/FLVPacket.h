#pragma once

#include <string>
#include <stdint.h>

enum FLVHeaderMode {
    AUDIO = 4,
    VIDEO = 1,
    AUDIO_AND_VIDEO = 5,
};

typedef struct FLVHeader {
    std::string signature;
    uint8_t version;
    FLVHeaderMode mediaTypeFlags;
    uint32_t headerSize;

    FLVHeader() :
            signature("FLV"),
            version(1),
            mediaTypeFlags(AUDIO_AND_VIDEO),
            headerSize(9)
    {

    }

    std::string getHeader() {
        return "";
    }
} FLVHeader_t;

class FLVPacket {
public:
    FLVPacket();
    ~FLVPacket();

    int dataLength;
private:

};
