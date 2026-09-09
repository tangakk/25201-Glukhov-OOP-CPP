cmake_minimum_required(VERSION 4.3)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(task-0)

add_executable(cpp
        task-0/csvmaker.cpp
        task-0/csvmaker.h
        task-0/main.cpp)
