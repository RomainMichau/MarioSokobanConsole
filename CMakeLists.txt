cmake_minimum_required(VERSION 3.0)
project(MarioSokobanConsole)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)


include_directories(utils)


add_executable(MarioSokobanConsole
        utils/console.cpp
        utils/console.h
        utils/coord.cpp
        utils/coord.h 
        src/BFSPLUS.cpp
        src/BFSPLUS.h
        src/case_morte.cpp
        src/case_morte.h
        src/chrono.cpp
        src/chrono.h
        src/heuristique.cpp
        src/heuristique.h
        src/main.cpp
        src/maze.cpp
        src/maze.h
        src/note.cpp
        src/note.h
    
        src/util.cpp
        src/util.h src/keyboardManager.cpp src/keyboardManager.h)
