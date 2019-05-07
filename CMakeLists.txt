cmake_minimum_required(VERSION 3.0)
project(MarioSokobanConsole)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)



add_executable(MarioSokobanConsole
#main
src/main.cpp
#Maze
src/Maze/Maze.cpp
src/Maze/Maze.h
#utils
src/utils/Console.cpp
src/utils/Console.h

src/utils/Coord.cpp 
src/utils/Coord.h 
		
src/utils/Chrono.cpp 
src/utils/Chrono.h
		
src/utils/Util.cpp
src/utils/Util.h  
			   
src/utils/KeyboardManager.cpp 
src/utils/KeyboardManager.h

#BFS_Stuff
src/BFS_Stuff/BFSPLUS.cpp
src/BFS_Stuff/BFSPLUS.h
	#Deadlocks
	src/BFS_Stuff/Deadlocks/Case_morte.cpp
    src/BFS_Stuff/Deadlocks/Case_morte.h
    #Heuristique
    src/BFS_Stuff/Heuristique/Heuristique.cpp
    src/BFS_Stuff/Heuristique/Heuristique.h
		#Note  
		src/BFS_Stuff/Heuristique/note.cpp
        src/BFS_Stuff/Heuristique/note.h  
	#BFS_Objects
	src/BFS_Stuff/BFS_Objects/MapStat.cpp 
	src/BFS_Stuff/BFS_Objects/MapStat.h
	src/BFS_Stuff/BFS_Objects/BFSCase.h
	src/BFS_Stuff/BFS_Objects/BFSCase.cpp
		#Mother_Class
		src/BFS_Stuff/BFS_Objects/Mother_Class/BFSCaseMother.cpp
		src/BFS_Stuff/BFS_Objects/Mother_Class/BFSCaseMother.h

         
          
        )
