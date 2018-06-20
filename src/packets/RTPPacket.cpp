#include "RTPPacket.h"

RTPPacket::RTPPacket(uint16_t sequenceNumber, uint32_t timeStamp, uint32_t synchronizationSourceId, std::string data) : data(data) {
    initializeDefaultHeader();

    header.sequenceNumber = sequenceNumber;
    header.timeStamp = timeStamp;
    header.synchronizationSourceId = synchronizationSourceId;
}

RTPPacket::~RTPPacket() {

}

std::string RTPPacket::getNetworkMessage() {
    // std's <bitset> class might be a more efficient alternative.
    char response[HEADER_LENGTH];
    std::size_t length = HEADER_LENGTH + data.length();

    response[0] = 0;

    response[0] |= header.version << 6;
    response[0] |= header.hasPadding << 5;
    response[0] |= header.hasExtension << 4;
    response[0] |= header.NumberOfContributingSourceIds;


    response[1] = 0;

    response[1] |= header.hasSpecialData << 7;
    response[1] |= header.payloadType;



    int position = setBytes(response, header.sequenceNumber, 2, sizeof(header.sequenceNumber));
    position = setBytes(response, header.timeStamp, position, sizeof(header.timeStamp));
    position = setBytes(response, header.synchronizationSourceId, position, sizeof(header.synchronizationSourceId));
    position = setBytes(response, header.contributingSourceId, position, sizeof(header.contributingSourceId));

    std::string message = std::string(response);

    return std::string(response, HEADER_LENGTH) + data;

}

void RTPPacket::printBinaryInformation() {
    std::string message = getNetworkMessage();

    for (std::size_t i = 0; i < message.size(); ++i) {
        char byte = message.c_str()[i];
        std::cout << std::bitset<8>(byte) << "    " << byte << std::endl;
    }
}

std::size_t RTPPacket::setBytes(char* destination, uint32_t source, std::size_t startIndex, std::size_t sourceBytes) {
    for (std::size_t i = startIndex; i < (startIndex + sourceBytes); ++i) {
        destination[i] = (source >> ((i - startIndex) * 8)) & 0xff;
    }

    return startIndex + sourceBytes;
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
