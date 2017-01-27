#pragma once

#include <stdint.h>
#include <iostream>

class RTPPacket {
public:
    RTPPacket(uint16_t sequenceNumber, uint32_t timeStamp, uint32_t synchronizationSourceId);
    ~RTPPacket();

    int8_t getVersion();
private:
    typedef struct {
        unsigned int version:2;
        // indicates if padding is used at the end of the RTP packet
        unsigned int hasPadding:1;
        // indicates the presense of an extension header between the RTP header and RTP payload data
        unsigned int hasExtension:1;
        unsigned int NumberOfContributingSourceIds:4;
        unsigned hasSpecialData:1;
        unsigned payloadType:7;
        uint16_t sequenceNumber;

        // timestamp represents the current position in time in the data stream.
        // For example in a 30 FPS video, where 1 frame is sent per RTP packet,
        //  the timestamp value should increase by 3000 for every new frame that
        //  is sent in the packet.
        uint32_t timeStamp;

        // the synchronization source ID is used as a unnique ID to identify a stream.
        // every packet in the same RTP stream should have the same synchronization source ID.
        uint32_t synchronizationSourceId;

        // we do not support any contributing source IDs.
        uint32_t contributingSourceId;
    } header_t;

    void initializeDefaultHeader();

    header_t header;
};
