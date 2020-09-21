cmake_minimum_required(VERSION 3.17)
project(brainfuck)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/brainfuck.cpp
        src/brainfuck.hpp
        src/main.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC
        -Wall
        -Wextra
        -Wpedantic
        -Werror)
