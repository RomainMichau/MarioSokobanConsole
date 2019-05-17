#ifndef FHEURISTIQUE_H
#define FHEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"

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
	FHeuristique(Maze *m) ;
	virtual ~FHeuristique();
	 AHeuristique* getInstance( int coefA, int coefB);


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
	short calcPivotPointPos(std::vector<short> distMap,  std::vector<short> freqMap);

	bool checkIfPivotLevel(short pivotPos);


};


#endif // HEURISTIQUE_H
