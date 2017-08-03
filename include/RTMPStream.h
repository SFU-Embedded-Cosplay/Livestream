#pragma once

#include <librtmp/rtmp.h>

#include "FLVPacket.h"

#include <string>
#include <iostream>
#include "assert.h"

#include "FLVPacket.h"

class RTMPStream {
public:

    RTMPStream(std::string url, uint32_t streamDurationInMilliseconds);
    ~RTMPStream();

    void startStream();

private:
    RTMP *rtmp = NULL;
    std::string url;

    static const uint32_t DEFAULT_TIMEOUT = 5;
};
