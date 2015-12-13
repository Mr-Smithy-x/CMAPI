cmake_minimum_required(VERSION 3.3)
project(CMAPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ps3utils/PS3Client.cpp ps3utils/PS3Client.h CMAPI.cpp CMAPI.h ps3utils/Response.cpp ps3utils/Response.h)
add_executable(CMAPI ${SOURCE_FILES})