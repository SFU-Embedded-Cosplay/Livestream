#include "RTMPStream.h"

RTMPStream::RTMPStream(std::string url, uint32_t streamDurationInMilliseconds) : url(url) {
    rtmp = RTMP_Alloc();
    RTMP_Init(rtmp);

    rtmp->Link.timeout = DEFAULT_TIMEOUT;

    if (!RTMP_SetupURL(rtmp, (char*) this->url.c_str())) {
        RTMP_Free(rtmp);
        std::cout << "failed to set up RTMP url\n";
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
        std::cout << "failed to connect to the RTMP server\n";
        RTMP_Free(rtmp);
        assert(false);
    }

    if (!RTMP_ConnectStream(rtmp, 0)) {
        std::cout << "failed to connect RTMP stream to the server\n";
        RTMP_Close(rtmp);
        RTMP_Free(rtmp);
        assert(false);
    }
}

void sendFrame(FLVPacket packet) {
    uint32_t currentTime = RTMP_GetTime();

    uint32_t dataLength = 0;

}
