/**
 * \file FHeurisitique.cpp
 * \brief declaration of the class FHeurisitique
 * \author romain michau
 * \version 2.1
 */

#ifndef FHEURISTIQUE_H
#define FHEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.h"
#include <unordered_map>
/**
* Factory de l'heuristique
* methode getInstance renvoit:
**	HeuritiquePivot si il s'agit d'un niveau avec une possiblité d'appliqer une heurtique pivot
**	sinon Heuristique classique
*/
class FHeuristique
{
public:





public:
    FHeuristique(Maze *m, int coefA, int coefB) ;
    virtual ~FHeuristique();
    /**
    * return the most appropriate tpye of heurisitque in function of the MAze
    *	Pivot Heuritique
    *	or
    *	Classical Heuristique
    */
    AHeuristique* getInstance();

    HeuristiqueClassique* getClassicalHeuritique();


private:

    Maze *m;
    Util u;


    /**
    * Stat calculators
    */
    std::vector<short> calcFrequentationSquares();
    std::vector<short> calcMapDistanceFromNearestGoals();


    /**
    * return the pivot point of mapStat
    * definit of pivotPoint: the point with the most frequentation.
    * if there is many point with the same max frequentation, then the farest from the goal win
    * @see MapStat
    */
	short calcPivotPointPos(std::vector<short> distMap, std::vector<short> freqMap);
	std::unordered_map<short,short> tunnelDetector();

    bool checkIfPivotLevel(short pivotPos);

    int coefA,coefB;
	

};


#endif // HEURISTIQUE_H
