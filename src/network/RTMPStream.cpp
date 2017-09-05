#include "RTMPStream.h"

RTMPStream::RTMPStream(std::string url, uint32_t streamDurationInMilliseconds) : url(url), header() {
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

    startTime = RTMP_GetTime();

    // int ret = RTMP_Write(rtmp, (char *) header.getHeader().c_str(), 9);
    // std::cout << ret << std::endl;
}

void RTMPStream::sendFrame(FLVPacket packet) {
    uint32_t currentTime = RTMP_GetTime() - startTime;

    uint32_t dataLength = 0;

}

void RTMPStream::sendData(char *data, uint32_t length) {
    RTMPPacket packet;
    packet.m_nChannel = 0x4; // video type
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_packetType = RTMP_PACKET_TYPE_VIDEO;
    packet.m_nTimeStamp = RTMP_GetTime() - startTime;
    packet.m_nInfoField2 = rtmp->m_stream_id;
    packet.m_hasAbsTimestamp = TRUE;

    packet.m_nBodySize = length;
    packet.m_body = data;

    std::cout << "sending\n" << length << "   ->   "  << packet.m_nBodySize << "\n";

    if(!RTMP_SendPacket(rtmp, &packet, FALSE))
    {
        std::cout << "could not send packet\n";
    }
    // if(!RTMP_Write(rtmp, data, length)) {
    //     std::cout << "write failed\n";
    // }
}
