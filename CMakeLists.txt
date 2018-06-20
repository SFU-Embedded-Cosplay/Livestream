cmake_minimum_required(VERSION 2.8)

project(livestream)

include_directories(${CMAKE_SOURCE_DIR}/include)

# set compiler for cross compilation
#SET(CMAKE_C_COMPILER   arm-linux-gnueabi-gcc)
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)

set(CMAKE_CXX_FLAG "-g -Wall -std=c++0x")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")


add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(tools)
add_subdirectory(test)
