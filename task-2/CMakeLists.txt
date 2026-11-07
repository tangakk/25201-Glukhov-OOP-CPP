project(task-0)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        task-2
        view/View.cpp
        model/Universe.cpp
        model/LifeFileReader.cpp
        model/LifeFileWriter.cpp
        controller/Controller.cpp
        controller/ArgvParser.cpp
        main.cpp)