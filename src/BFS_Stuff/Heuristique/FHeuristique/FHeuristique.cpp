#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.h"
#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.h"
#include "FHeuristique.h"

FHeuristique::FHeuristique()
{
}

FHeuristique::~FHeuristique()
{
}

AHeuristique * FHeuristique::getInstance(Maze * m, int coefA, int coefB)
{
	return new HeuristiquePivot(m, coefA, coefB);
}
