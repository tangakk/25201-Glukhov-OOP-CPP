project(task-0)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        task-0
        Parser.cpp
        Parser.h
        FileReader.cpp
        FileReader.h
        StatisticsStorage.cpp
        StatisticsStorage.h
        CSVFileWriter.h
        CSVFileWriter.inl
        CSVFileWriter.cpp
        main.cpp)