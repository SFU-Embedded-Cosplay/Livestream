#include <iostream>
#include <string>

#include "RTPPacket.h"
#include "Camera.h"

int main(int argc, char** argv) {
    RTPPacket packet(0, 0, 256);

    std::cout << "This RPT packet is using version #" << packet.getVersion() << std::endl;
    Camera cam;
}
