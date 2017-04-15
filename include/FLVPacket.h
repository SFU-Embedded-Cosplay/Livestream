#pragma once

#include <string>
#include <stdint.h>

#include "FLVHeader.h"

// note that all 2 byte or more numbers, in an flv packet / header, are stored using Big Endian.

class FLVPacket {
public:
    FLVPacket();
    ~FLVPacket();
private:

};
