add_library(network RTPPacket.cpp UDPClient.cpp UDPServer.cpp)

target_link_libraries(network "librtmp.a")
