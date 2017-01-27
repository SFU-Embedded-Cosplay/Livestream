#include "RTPPacket.h"

RTPPacket::RTPPacket(uint16_t sequenceNumber, uint32_t timeStamp, uint32_t synchronizationSourceId) {
    initializeDefaultHeader();


    header.sequenceNumber = sequenceNumber;
    header.timeStamp = timeStamp;
    header.synchronizationSourceId = synchronizationSourceId;
}

RTPPacket::~RTPPacket() {

}

int8_t RTPPacket::getVersion() {
    return header.version; //16
}

void RTPPacket::initializeDefaultHeader() {
    header.version = 2;
    header.hasPadding = false;
    header.hasExtension = false;
    header.NumberOfContributingSourceIds = 0;
    header.hasSpecialData = false;
    // use JPEG encoded video (no audio) to start off
    unsigned int jpegEncodedVideoPayloadTypeID = 26;
    // appropriate values for payloadType can be found in rfc3551 section 6 or https://en.wikipedia.org/wiki/RTP_audio_video_profile
    header.payloadType = jpegEncodedVideoPayloadTypeID;

    header.contributingSourceId = 0;
}
