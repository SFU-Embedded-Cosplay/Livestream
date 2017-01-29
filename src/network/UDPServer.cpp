#include "UDPServer.h"

UDPServer::UDPServer(int port) {
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(socketFileDescriptor, (struct sockaddr *)&client, sizeof(client)) < 0) {
        std::cout << "Server could not bind to port: " + port << std::endl;
        std::cout << "Exiting the programs" << std::endl;
        exit(EXIT_FAILURE);
    }
}

UDPServer::~UDPServer() {
    close(socketFileDescriptor);
}

std::string UDPServer::receive() {
    char buffer[BUFFER_LENGTH];
    socklen_t clientLength = sizeof(client);
    int receivedBytes = recvfrom(socketFileDescriptor, buffer, BUFFER_LENGTH, 0, (struct sockaddr *)&client, &clientLength);
    return std::string(buffer);
}
