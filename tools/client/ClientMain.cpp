#include <iostream>
#include <string>

#include "RTPPacket.h"
#include "UDPClient.h"
#include "UDPServer.h"
#include "Camera.h"

#include <bitset>

int main() {

    // Camera cam;
    RTPPacket packet(260, 0, 1024, "hello world");
    std::string msg = packet.getNetworkMessage();

    std::cout << msg << ": "<< msg.size() << std::endl;

    // std::cout << cam.getFrame().size() << std::endl;

    UDPClient udp("127.0.0.1", 8080);
    UDPServer server(8081);

    udp.send("hello world");
    std::cout << "client received: '" + server.receive() + "'" << std::endl;

    return 0;
}
