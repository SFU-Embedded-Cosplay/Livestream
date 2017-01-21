#include "RTPPacket.h"

RTPPacket::RTPPacket() {
    version = 2;
}

RTPPacket::~RTPPacket() {

}

int8_t RTPPacket::getVersion() {
    return version;
}
