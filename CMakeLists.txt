cmake_minimum_required(VERSION 3.0)
project(MarioSokobanConsole)

set(CMAKE_CXX_STANDARD 14)



include_directories(.)
include_directories(/levels)

    
   
add_executable(MarioSokobanConsole
#main
src/main.cpp
#Maze
src/Maze/Maze.cpp
src/Maze/Maze.h 

src/Maze/GameState.h
src/Maze/GameState.cpp 
#utils
src/utils/Console.cpp
src/utils/Console.h
 
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
	src/BFS_Stuff/Deadlocks/Case_morte.cpp
    src/BFS_Stuff/Deadlocks/case_morte.h
    #Heuristique
    src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.cpp
    src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.h
    src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.cpp
    src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.h
    src/BFS_Stuff/Heuristique/MacroMover/MacroMover.cpp
    src/BFS_Stuff/Heuristique/MacroMover/MacroMover.h
		#Note  
		src/BFS_Stuff/Heuristique/note.cpp
        src/BFS_Stuff/Heuristique/note.h  
		#Mother_Class
		src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h
		src/BFS_Stuff/Heuristique/Abstract/AHeuristique.cpp
		#Factroy
		src/BFS_Stuff/Heuristique/FHeuristique/FHeuristique.cpp
		src/BFS_Stuff/Heuristique/FHeuristique/FHeuristique.h

	#BFS_Objects
	
	src/BFS_Stuff/BFS_Objects/Node.h
	src/BFS_Stuff/BFS_Objects/Node.cpp 
	src/BFS_Stuff/BFS_Objects/Chapter.h
	src/BFS_Stuff/BFS_Objects/Chapter.cpp
		#Mother_Class
		src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.cpp
		src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.h



         
          
)
