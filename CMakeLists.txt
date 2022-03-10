cmake_minimum_required(VERSION 3.21)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(LearnOpenGL
        src/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)