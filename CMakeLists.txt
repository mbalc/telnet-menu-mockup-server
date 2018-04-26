cmake_minimum_required(VERSION 3.10)
project(1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(1
        src/ansi.h
        src/echo-server.cc
        src/err.cc
        src/err.h)
