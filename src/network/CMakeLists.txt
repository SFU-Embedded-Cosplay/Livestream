add_library(network RTPPacket.cpp UDPClient.cpp UDPServer.cpp RTMPStream.cpp)

target_link_libraries(network "librtmp.a")
