#include <iostream>
#include <string>

#include "RTPPacket.h"
#include "UDPClient.h"
#include "UDPServer.h"
#include "Camera.h"

int main(int argc, char** argv) {
    RTPPacket packet(0, 0, 256, "test data");

    std::cout << "This RPT packet is using version #" << packet.getVersion() << std::endl;

    UDPServer server(8080);
    std::string message = server.receive();

    UDPClient client("127.0.0.1", 8081);
    client.send("server response");


    // udp.send("I got your message. it was: " + message);

    std::cout << "server received message " + message + " and sent back a message" << std::endl;

}
