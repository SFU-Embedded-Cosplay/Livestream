#pragma once
#include <string>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


class UDPClient {
public:
    UDPClient(std::string serverIpAddress, int serverPort);
    ~UDPClient();
    void send(std::string message);
private:
    std::string serverIpAddress;
    int serverPort;

    int socketFileDescriptor;
    struct sockaddr_in serverAddress;

};
