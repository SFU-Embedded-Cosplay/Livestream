add_library(network UDPClient.cpp UDPServer.cpp RTMPStream.cpp)

target_link_libraries(network "librtmp.a")
