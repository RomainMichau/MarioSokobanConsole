
#include "maze.h"
#include "../utils/console.h"
#include "../utils/coord.h"
#include "keyboardManager.h"
#include <iostream>
#include <stdio.h>
#include "BFSPLUS.h"
#include "heuristique.h"
#include "chrono.h"
#include "util.h"
#include "case_morte.h"

int noteA;
int noteB;

std::vector<unsigned char>  goHeursitique(Maze m, chrono &chr, bool dispTime, int &noeudVisite)
{

	BFSPLUS killa_bfs;
	std::vector<unsigned char> chemin;
	chemin = killa_bfs.bfs_malin(m, noeudVisite, 1, 2, 50000000);
	return chemin;

}

void testHeuristiqueXTime(int xtime, Maze m, chrono &chr, int &noeudVisite)
{

	for (int i = 0; i < xtime; i++)
	{
		goHeursitique(m, chr, false, noeudVisite);
	}
}



void testBestCoefHeuristique(Maze m, chrono &chr, int mine, int maxe, int plafond, int pas)
{

	int noeudVisite;
	long bestnoeud = 1000000;
	int bestnoteA;
	int bestnoteB;
	int cpt = 0;
	BFSPLUS killa_bfs;
	for (noteA = mine; noteA <= maxe; noteA += pas)
	{
		for (noteB = mine; noteB <= maxe; noteB += pas)
		{
			cpt++;
			killa_bfs.reinit();
			m.reinit();

			killa_bfs.bfs_malin(m, noeudVisite, noteA, noteB, 50000000);

			if (noeudVisite < bestnoeud)
			{
				bestnoeud = noeudVisite;
				bestnoteA = noteA;
				bestnoteB = noteB;
				std::cout << std::endl << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
				std::cout << "best noeud:" << bestnoeud << std::endl << "best noteA:" << bestnoteA << "  best noteB:" << bestnoteB << std::endl;
				std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl << std::endl;

			}
			if (cpt % 100 == 0)
				std::cout << "cpt:" << cpt << std::endl << "note A:" << noteA << std::endl << "noteB:" << noteB << "temps: " << chr.temps_ecoule() << std::endl;
		}
	}
}



int main()
{

	//std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
	std::cout << "///////////////////////////MARIO SOKOBAN SOLVER///////////////////////////" << std::endl;
	util u;

	Console::getInstance()->setColor(_COLOR_DEFAULT);
	std::vector<unsigned char> chemin;
	std::string path = u.choose_level();

	// Load level from a file
	Maze m(path);

	keyboardManager g;
	heuristique h;
	chrono chr;
	BFSPLUS killa_bfs;
	case_morte Lamoort;
	bool auto_mode = false;
	if (!m.init())
		return -1;

	int noeudvisite = 0;

	std::cout << m << std::endl;
	std::vector<unsigned char> vec = m.getField();
	m.setFieldOr(vec);

	m.setPlayerPosOr(m.getPosPlayer());
	Lamoort.detect_dead_with_BFS(m);
	std::cout << m << std::endl;


	if (g.init())
	{
		while (true)
		{
			while (!g.keyPressed())
			{

			}
			// Check if user has pressed a key
			if (!auto_mode)
			{
				bool win = false;
				char key = g.keyRead();
				switch (key)
				{
				case ARROW_UP:
					win = m.updatePlayer(TOP);
					break;
				case ARROW_BOTTOM:
					win = m.updatePlayer(BOTTOM);
					break;
				case ARROW_RIGHT:
					win = m.updatePlayer(RIGHT);
					break;
				case ARROW_LEFT:
					win = m.updatePlayer(LEFT);
					break;
				case 53:
					//DEADLOCKS DYNAMIQUE
				{
					std::cout << "BEST BFS";
					chr.lancer_chrono();

					chemin = goHeursitique(m, chr, false, noeudvisite);

					auto_mode = true;
				}
				break;
				}


				/**
				*Montre le trajet à la fin de la partie
				*/
				if (auto_mode)
				{

					m.drawMove(chemin, chr.temps_ecoule(), noeudvisite);

					auto_mode = false;
					win = true;
				}

				if (win)
				{
					std::cout << "Win ! " << std::endl;
					break;
				}
			}
		}

		// Display on screen



	}


	// Free memory
	Console::deleteInstance();
	system("pause");
	return 0;
}

