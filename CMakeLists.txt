cmake_minimum_required(VERSION 3.6)
project(ABF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp
        Point.cpp Point.h
        Forest.cpp Forest.h
        Player.cpp Player.h )
add_executable(ABF ${SOURCE_FILES})
