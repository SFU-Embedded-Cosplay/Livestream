#include <iostream>
#include <string>

#include "RTPPacket.h"
#include "UDPClient.h"
#include "UDPServer.h"
#include "Camera.h"

int main() {

    // Camera cam;
    RTPPacket packet(0, 0, 5000);

    // std::cout << cam.getFrame().size() << std::endl;

    UDPClient udp("127.0.0.1", 8080);
    UDPServer server(8081);

    udp.send("hello world");
    std::cout << "client received: '" + server.receive() + "'" << std::endl;

    return 0;
}
