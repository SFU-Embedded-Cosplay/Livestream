#pragma once

#include <string>
#include <stdint.h>

// note that all 2 byte or more numbers, in an flv packet / header, are stored using Big Endian.

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
        char header[headerSize];
        header[0] = signature.at(0);
        header[1] = signature.at(1);
        header[2] = signature.at(2);

        header[3] = version;

        header[4] = mediaTypeFlags;

        // copy header size as big endian value to char array.
        header[5] = headerSize >> 24;
        header[6] = headerSize >> 16;
        header[7] = headerSize >> 8;
        header[8] = headerSize >> 0;
        return std::string(header, headerSize);
    }
} FLVHeader_t;
