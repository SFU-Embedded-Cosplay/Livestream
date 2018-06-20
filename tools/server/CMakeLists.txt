add_executable(server ServerMain.cpp)

target_link_libraries(server network)
target_link_libraries(server camera)
target_link_libraries(server packets)
