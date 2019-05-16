#ifndef FHEURISTIQUE_H
#define FHEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"

class FHeuristique 
{
public:





public:
	FHeuristique();
	virtual ~FHeuristique();
	static AHeuristique* getInstance(Maze *m, int coefA, int coefB);




};


#endif // HEURISTIQUE_H
