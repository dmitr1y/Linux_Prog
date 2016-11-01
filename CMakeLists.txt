cmake_minimum_required(VERSION 3.6)
project(Alco)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp functions.h)
add_executable(Alco ${SOURCE_FILES})