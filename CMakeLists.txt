cmake_minimum_required(VERSION 3.8)
project(ex4Server)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Server.cpp Server.h FileReader.cpp FileReader.h)
add_executable(ex4Server ${SOURCE_FILES})