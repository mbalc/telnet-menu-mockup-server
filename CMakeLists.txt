cmake_minimum_required(VERSION 3.10)
project(1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CCXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")

include_directories(.)

add_executable(1
        src/defs.h
        src/echo-server.cc
        src/err.cc
        src/err.h src/entry.cc src/entry.h src/menu.cc src/menu.h src/example-data.h src/socketStream.h src/socketStream.cc)
