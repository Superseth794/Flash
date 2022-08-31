cmake_minimum_required(VERSION 3.17)
project(Flash)

set(CMAKE_CXX_STANDARD 17)

add_executable(Flash src/main.cpp
        src/image/PPMImage.cpp)