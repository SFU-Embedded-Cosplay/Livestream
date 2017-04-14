add_executable(client ClientMain.cpp)

target_link_libraries(client network)
target_link_libraries(client camera)
target_link_libraries(client packets)
