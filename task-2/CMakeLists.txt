project(task-0)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        task-2
        model/Universe.cpp
        model/LifeFileReader.cpp
        model/LifeFileWriter.cpp
        controller/Controller.cpp
        controller/ArgvParser.cpp
        controller/Command.cpp
        controller/CommandParser.cpp
        ../task-0/FileReader.cpp
        main.cpp)