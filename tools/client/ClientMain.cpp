#include <iostream>
#include <string>

#include "RTPPacket.h"
#include "Camera.h"

int main() {

    Camera cam;
    std::cout << cam.getFrame().size() << std::endl;

    return 0;
}
