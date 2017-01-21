#pragma once

#include <stdint.h>

class RTPPacket {
public:
    RTPPacket();
    ~RTPPacket();

    int8_t getVersion();
private:
    int8_t version;
};
