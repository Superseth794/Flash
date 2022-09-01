cmake_minimum_required(VERSION 3.17)
project(Flash)

set(CMAKE_CXX_STANDARD 17)

add_executable(Flash src/main.cpp
        src/image/PPMImage.cpp
        src/utils/Color.cpp include/physics/Ray.h include/physics/Collider.h src/physics/Sphere.cpp include/physics/Sphere.hpp src/physics/Collider.cpp src/Renderer/Scene.cpp include/Renderer/Scene.hpp)