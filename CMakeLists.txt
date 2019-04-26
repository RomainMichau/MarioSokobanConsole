cmake_minimum_required(VERSION 3.14)
project(MarioSokoban)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)


include_directories(utils)


add_executable(MarioSokoban
        include/BFSPLUS.h
        include/marque_field.h
        utils/console.cpp
        utils/console.h
        utils/coord.cpp
        utils/coord.h
        src/BFS.cpp
        src/BFS.h
        src/BFSPLUS.cpp
        src/BFSPLUS.h
        src/bruteforce.cpp
        src/bruteforce.h
        src/case_morte.cpp
        src/case_morte.h
        src/chrono.cpp
        src/chrono.h
        src/DFS.cpp
        src/DFS.h
        src/heuristique.cpp
        src/heuristique.h
        src/main.cpp
        src/maze.cpp
        src/maze.h
        src/note.cpp
        src/note.h
        src/stock_field.cpp
        src/stock_field.h
        src/util.cpp
        src/util.h src/keyboardManager.cpp src/keyboardManager.h)
