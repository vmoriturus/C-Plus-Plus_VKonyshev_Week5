cmake_minimum_required(VERSION 3.27)
project(ring_buffer_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ring_buffer_2 main.cpp
        ringbuff.hpp)
