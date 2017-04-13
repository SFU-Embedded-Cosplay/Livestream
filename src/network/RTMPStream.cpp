#include "RTMPStream.h"

RTMPStream::RTMPStream(std::string url, uint32_t streamDurationInMilliseconds) {
    rtmp = RTMP_Alloc();
    RTMP_Init(rtmp);

    rtmp->Link.timeout = DEFAULT_TIMEOUT;

    char buffer[url.length() + 1];
    url.copy(buffer, url.length());

    if (!RTMP_SetupURL(rtmp, buffer)) {
        RTMP_Free(rtmp);
        assert(false);
    }

    RTMP_EnableWrite(rtmp);

    // 3600 * 1000 = 1 hour
    RTMP_SetBufferMS(rtmp, streamDurationInMilliseconds);
}

RTMPStream::~RTMPStream() {
    if (rtmp != NULL) {
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        rtmp = NULL;
    }
}

void RTMPStream::startStream() {
    if (!RTMP_Connect(rtmp, NULL)) {
        RTMP_Free(rtmp);
        assert(false);
    }

    if (!RTMP_ConnectStream(rtmp, 0)) {
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        assert(false);
    }
}

void sendFrame(flv_packet_t packet) {
    uint32_t currentTime = RTMP_GetTime();

    uint32_t dataLength = packet.dataLength;

}
