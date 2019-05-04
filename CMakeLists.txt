cmake_minimum_required(VERSION 3.0)
project(MarioSokobanConsole)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)



add_executable(MarioSokobanConsole
#main
src/main.cpp
#Maze
src/Maze/maze.cpp
src/Maze/maze.h
#utils
src/utils/console.cpp
src/utils/console.h

src/utils/coord.cpp
src/utils/coord.h 
		
src/utils/chrono.cpp
src/utils/chrono.h
		
src/utils/util.cpp
src/utils/util.h 
		
src/utils/keyboardManager.cpp 
src/utils/keyboardManager.h

#BFS_Stuff
src/BFS_Stuff/BFSPLUS.cpp
src/BFS_Stuff/BFSPLUS.h
	#Deadlocks
	src/BFS_Stuff/Deadlocks/case_morte.cpp
    src/BFS_Stuff/Deadlocks/case_morte.h
    #Heuristique
    src/BFS_Stuff/Heuristique/heuristique.cpp
    src/BFS_Stuff/Heuristique/heuristique.h
		#Note 
		src/BFS_Stuff/Heuristique/note.cpp
        src/BFS_Stuff/Heuristique/note.h  
	#BFS_Objects
	src/BFS_Stuff/BFS_Objects/MapStat.cpp
	src/BFS_Stuff/BFS_Objects/MapStat.h
        
        
          
        )
