#pragma once

#include <stdint.h>
#include <iostream>
#include <string>

class RTPPacket {
public:
    RTPPacket(uint16_t sequenceNumber, uint32_t timeStamp, uint32_t synchronizationSourceId, std::string data);
    ~RTPPacket();

    std::string getNetworkMessage();

    static const int HEADER_LENGTH = 16; // 16 bytes
private:
    typedef struct {
        /* FIRST BYTE */
        unsigned int version:2;
        // indicates if padding is used at the end of the RTP packet
        unsigned int hasPadding:1;
        // indicates the presense of an extension header between the RTP header and RTP payload data
        unsigned int hasExtension:1;
        unsigned int NumberOfContributingSourceIds:4;

        /* SECOND BYTE */
        unsigned hasSpecialData:1;
        unsigned payloadType:7;

        /* BYTE 3-4 */
        uint16_t sequenceNumber;

        // timestamp represents the current position in time in the data stream.
        // For example in a 30 FPS video, where 1 frame is sent per RTP packet,
        //  the timestamp value should increase by 3000 for every new frame that
        //  is sent in the packet.
        /* BYTE 5-8 */
        uint32_t timeStamp;

        // the synchronization source ID is used as a unnique ID to identify a stream.
        // every packet in the same RTP stream should have the same synchronization source ID.
        /* BYTE 9-12 */
        uint32_t synchronizationSourceId;

        // we do not support any contributing source IDs.
        /* BYTE 13-16 */
        uint32_t contributingSourceId;
    } header_t;

    void initializeDefaultHeader();
    int setBytes(char* destination, uint32_t source, int startIndex, int sourceBytes);

    header_t header;
    std::string data;
};
