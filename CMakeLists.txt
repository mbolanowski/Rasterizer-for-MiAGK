cmake_minimum_required(VERSION 3.30)
project(1)

set(CMAKE_CXX_STANDARD 20)

add_executable(1 main.cpp
        Renderer.h
        Renderer.cpp
        Triangle.h
        Triangle.cpp
        Color.h)
