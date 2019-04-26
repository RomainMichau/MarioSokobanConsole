/**********************************'**************************
Sokoban project - Main file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/
#include "maze.h"
#include "bruteforce.h"
#include "../utils/console.h"
#include "../utils/coord.h"
#include "keyboardManager.h"
#include <iostream>
#include <stdio.h>
#include "BFSPLUS.h"
#include "heuristique.h"
#include "DFS.h"
#include "chrono.h"
#include "BFS.h"
#include "util.h"
#include "case_morte.h"
#include "stock_field.h"
// Init allegro with 800x600 (chemin)

int noteA;
int noteB;

std::vector<unsigned char>  goHeursitique(Maze m,chrono &chr,bool dispTime,int &noeudVisite)
{

    BFSPLUS killa_bfs;
    std::vector<unsigned char> chemin;
    chemin=killa_bfs.bfs_malin(m,false, noeudVisite,1,300,50000000);




    return chemin;

}

void testHeuristiqueXTime(int xtime,Maze m,chrono &chr,int &noeudVisite)
{

    for (int i=0; i<xtime; i++)
    {
        goHeursitique( m, chr,false,noeudVisite);
    }
}



void testBestCoefHeuristique(Maze m,chrono &chr,int mine,int maxe,int plafond,int pas)
{

    int noeudVisite;
    long bestnoeud=1000000;
    int bestnoteA;
    int bestnoteB;
    int cpt=0;
    BFSPLUS killa_bfs;
    for(noteA=mine; noteA<=maxe; noteA+=pas)
    {
        for(noteB=mine; noteB<=maxe; noteB+=pas)
        {
            cpt++;
            killa_bfs.reinit();
            m.reinit();

            killa_bfs.bfs_malin(m,false, noeudVisite,noteA,noteB,plafond);

            if(noeudVisite<bestnoeud)
            {
                bestnoeud=noeudVisite;
                bestnoteA=noteA;
                bestnoteB=noteB;
                std::cout<<std::endl<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<std::endl;
                std::cout<<"best noeud:"<<bestnoeud<<std::endl<<"best noteA:"<<bestnoteA<<"  best noteB:"<<bestnoteB<<std::endl;
                std::cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<std::endl<<std::endl;

            }
            if(cpt%100==0)
                std::cout<<"cpt:"<<cpt<<std::endl<<"note A:"<<noteA<<std::endl<<"noteB:"<<noteB<<"temps: "<<chr.temps_ecoule()<<std::endl;
        }
    }
}



int main()
{

//std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    std::cout<<"///////////////////////////MARIO SOKOBAN SOLVER///////////////////////////"<<std::endl;
    util u;

    Console::getInstance()->setColor(_COLOR_DEFAULT);
    std::vector<unsigned char> chemin;
    std::string path=u.choose_level();

    // Load level from a file
    Maze m(path);

    keyboardManager g;
    Bruteforce labrutace;
    BFS le_poto_b;
    heuristique h;
    chrono chr;
    DFS le_poto_d;
    BFSPLUS killa_bfs;
    case_morte Lamoort;
    bool auto_mode=false;
    if (!m.init())
        return -1;

    int noeudvisite=0;

    std::cout << m << std::endl;
    std::vector<unsigned char> vec=m.getField();
    m.setFieldOr(vec);

    m.setPlayerPosOr(m.getPosPlayer());
    Lamoort.detect_dead(m);
    if (g.init())
    {
        // While playing...

        while(true)
        {
            while(!g.keyPressed())
            {

            }
            // Check if user has pressed a key
            if (!auto_mode)
            {
                bool win = false;
                char key=g.keyRead();
                std::cout<<"key"<<key<<std::endl;
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

                case KEY_R:

                    // djiki.heuristiquemaline(m);
                    m.reinit();
                    le_poto_b.reinit();
                    le_poto_d.reinit();
                    killa_bfs.reinit();
                    break;
                case KEY_1:

                {
                    chr.lancer_chrono();
                    std::cout<<"//////////////////////////////////////////////////////////////////////"<<std::endl;
                    std::cout<<"WARNING!!!  BRUTEFORCE ACTIVE!!!"<<std::endl;
                    chemin=labrutace.forcage(m);
                    if(chemin[0]!='s')
                    {
                        // rest(2000);
                        std::cout<<"bruteforce succesfull"<<std::endl<<"nb de coup:"<<chemin.size()<<std::endl<<std::endl;
                        auto_mode=true;
                    }

                }
                break;
                case KEY_2:

                {
                    chr.lancer_chrono();
                    std::cout<<"//////////////////////////////////////////////////////////////////////"<<std::endl;
                    std::cout<<"WARNING!!!  BFS ACTIVE!!!"<<std::endl;
                    chemin=le_poto_b.letsgobfs(m);
                    if(chemin[0]!='s')
                    {
                        //   rest(2000);
                        std::cout<<"bfs successfull"<<std::endl<<"nb de coup:"<<chemin.size()<<std::endl;
                        auto_mode=true;
                    }
                }
                break;

                case KEY_3:

                {
                    chr.lancer_chrono();
                    std::cout<<"//////////////////////////////////////////////////////////////////////"<<std::endl;
                    std::cout<<"WARNING!!!  DFS ACTIVE!!!"<<std::endl;
                    chemin=le_poto_d.letsgodfs(m);
                    if(chemin[0]!='s')
                    {
                        //   rest(2000);
                        std::cout<<"dfs successfull"<<std::endl<<"nb de coup:"<<chemin.size()<<std::endl;
                        auto_mode=true;

                    }
                }
                break;


                case 53:
                    //DEADLOCKS DYNAMIQUE
                {
                    std::cout<<"BEST BFS";
                    chr.lancer_chrono();

                    chemin= goHeursitique(m,chr,false,noeudvisite);

                    auto_mode=true;
                }
                break;

                case KEY_6:
                    //DEADLOCKS DYNAMIQUE
                {
                    chr.lancer_chrono();

                    testHeuristiqueXTime(300, m,chr,noeudvisite);
                    auto_mode=true;
                }
                break;


                case KEY_7:
                    //DEADLOCKS DYNAMIQUE
                {
                    int mi;
                    int ma;
                    int pas;
                    int plafond;
                    std::cout<<std::endl<<"min: ";
                    std::cin>>mi;
                    std::cout<<std::endl<<"max: ";
                    std::cin>>ma;
                    std::cout<<std::endl<<"pas: ";
                    std::cin>>pas;
                    std::cout<<std::endl<<"plafond: ";
                    std::cin>>plafond;
                    std::cout<<std::endl<<std::endl<<"Test coef | min:"<<mi<<" max:"<<ma<<" plafond:"<<plafond<<" pas:"<<pas<<std::endl;
                    chr.lancer_chrono();

                    testBestCoefHeuristique( m,chr,mi,ma,plafond,pas);
                    auto_mode=true;
                }
                break;




                }


                /**
                *Montre le trajet à la fin de la partie
                */
                if(auto_mode)
                {
                    std::cout<<"temps: "<<chr.temps_ecoule()<<" s"<<std::endl<<"noeuds visite:"<<noeudvisite<<std::endl<<std::endl;
                    std::cout<<"level: "<<path<<std::endl;
                    for(int i=0; i<chemin.size(); i++)
                    {
                        m.updatePlayer(chemin[i]);
                        m.draw();
                    }
                    auto_mode=false;
                    win =true;
                }

                if (win)
                {
                    std::cout << "Win ! " << std::endl;
                    break;
                }
            }
        }

        // Display on screen
        m.draw();


    }


    // Free memory
    Console::deleteInstance();
    system("pause");
    return 0;
}
