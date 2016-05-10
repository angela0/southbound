cmake_minimum_required(VERSION 3.3)
project(southbound)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    interface.cpp
    interface.h
    main.cpp
    processdata.cpp
    processdata.h)

add_executable(southbound ${SOURCE_FILES})