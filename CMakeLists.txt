cmake_minimum_required(VERSION 2.8)

project(livestream)

find_package(OpenCV REQUIRED )

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAG "-g -Wall -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")


add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(tools)
add_subdirectory(test)
