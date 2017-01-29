#include "UDPClient.h"

UDPClient::UDPClient(std::string serverIpAddress, int serverPort) : serverIpAddress(serverIpAddress), serverPort(serverPort) {
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = inet_addr(serverIpAddress.c_str());
}

UDPClient::~UDPClient() {
    close(socketFileDescriptor);
}

void UDPClient::send(std::string message) {
    socklen_t serverLength = sizeof(serverAddress);
    sendto(socketFileDescriptor, message.c_str(), message.length(), 0, (struct sockaddr *)&serverAddress, serverLength);
}
