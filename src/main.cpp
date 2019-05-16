
#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include "src/utils/KeyboardManager.h"
#include <iostream>
#include <stdio.h> 
#include "src/BFS_Stuff/BFSPLUS.h"
#include "src/BFS_Stuff/Heuristique/HeuristiquePivot.h"
#include "src/BFS_Stuff/Heuristique/HeuristiqueClassique.h"
#include "src/utils/Chrono.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h" 
#include "src/BFS_Stuff/Heuristique/FHeuristique/FHeuristique.h"

std::vector<unsigned char>  goHeursitique(Maze m, unsigned &noeudVisite)
{	
//	AHeuristique *heurC = new HeuristiqueClassique(&m, 1, 2);
	BFSPLUS killa_bfs(&m,FHeuristique::getInstance(&m,1,2));
	std::vector<unsigned char> chemin;
	chemin = killa_bfs.runBFS(noeudVisite);
	return chemin;

}	



int main()
{

	//std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
	std::cout << "///////////////////////////MARIO SOKOBAN SOLVER///////////////////////////" << std::endl;
	Util u;

	Console::getInstance()->setColor(_COLOR_DEFAULT);
	std::vector<unsigned char> chemin;
	std::string path = u.choose_level();
	// Load level from a file
	Maze m(path);

	KeyboardManager g;
	Chrono chr;
	if (!m.init())
		return -1;

	unsigned noeudvisite = 0;
	std::cout << m << std::endl;
	std::vector<unsigned char> vec = m.getField();
	m.setFieldOr(vec);


	m.setPlayerPosOr(m.getPosPlayer());
	Case_morte Lamoort(&m);
	Lamoort.detect_dead_with_BFS();
	std::cout << m << std::endl;
	//u.dispVector(m,	h.calcFrequentationSquares(m));

	while (true)
	{
		std::cout << "press space for launch BFS"<<std::endl;
		while (!g.keyPressed())
		{

		}
		// Check if user has pressed a key

		char key = g.keyRead();
		switch (key)
		{
		case ' ':
		case 53:
			//DEADLOCKS DYNAMIQUE

			std::cout << "BEST BFS";
			chr.lancer_chrono();
			chemin = goHeursitique(m, noeudvisite);
			break;
		}

		if (chemin.size() == 0) {
			std::cout << "no solution to this Maze :(";
			system("pause");
			return 0;
		}

		/**
		*Montre le trajet à la fin de la partie
		*/
		m.drawMove(chemin, chr.temps_ecoule(), noeudvisite);
		std::cout << "Win ! " << std::endl;
		break;
	}

	// Display on screen






	// Free memory
	Console::deleteInstance();
	system("pause");
	return 0;
}

