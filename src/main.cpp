
#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include "src/utils/KeyboardManager.h"
#include <iostream>
#include <stdio.h>
#include "src/BFS_Stuff/BFSPLUS.h"
#include "src/BFS_Stuff/Heuristique/Heuristique.h"
#include "src/utils/Chrono.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/DeadLocks/Case_morte.h"


std::vector<unsigned char>  goHeursitique(Maze m, unsigned &noeudVisite)
{

    BFSPLUS killa_bfs(&m);
    std::vector<unsigned char> chemin;
    chemin = killa_bfs.runBFS( noeudVisite, 1, 2);
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
    bool auto_mode = false;
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

                chemin = goHeursitique(m,   noeudvisite);
				if (chemin.size() == 0) {
					std::cout << "no solution to this Maze :(";
					system("pause");
					return 0;
				}
                auto_mode = true;
            }
            break;
            }


            /**
            *Montre le trajet � la fin de la partie
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






    // Free memory
    Console::deleteInstance();
    system("pause");
    return 0;
}

