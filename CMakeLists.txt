cmake_minimum_required(VERSION 4.3)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(task-0)

add_executable(task0
        task-0/main.cpp
        task-0/FileReader.h
        task-0/FileReader.cpp
        task-0/Parser.cpp
        task-0/Parser.h
        task-0/StatisticsStorage.cpp
        task-0/StatisticsStorage.h
        task-0/CSVFileWriter.cpp
        task-0/CSVFileWriter.h
        task-0/CSVFileWriter.inl)
