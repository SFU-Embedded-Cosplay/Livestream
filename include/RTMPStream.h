#pragma once

#include <librtmp/rtmp.h>
#include <librtmp/log.h>

#include "FLVHeader.h"
#include "FLVPacket.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "assert.h"

#include "FLVPacket.h"

class RTMPStream {
public:

    RTMPStream(std::string url, uint32_t streamDurationInMilliseconds);
    ~RTMPStream();

    void startStream();
    void sendFrame(FLVPacket packet);
    void sendData(char *data, uint32_t length);

private:
    RTMP *rtmp;
    std::string url;
    FLVHeader_t header;

    uint32_t startTime;

    static const uint32_t DEFAULT_TIMEOUT = 5;
};
