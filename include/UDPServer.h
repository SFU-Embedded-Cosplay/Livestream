#pragma once
#include <string>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>

class UDPServer {
public:
    UDPServer(int serverPort);
    ~UDPServer();
    std::string receive();


    const static size_t BUFFER_LENGTH = 4096;
private:
    int port;

    int socketFileDescriptor;
    struct sockaddr_in client;

};
