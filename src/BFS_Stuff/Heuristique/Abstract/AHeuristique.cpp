#include "AHeuristique.h"
#include <algorithm>
AHeuristique::AHeuristique(Maze *m, int coefA, int coefB,bool isPivotHeuristique) :
    m(m),note(Note(coefA, coefB, 50000)), deadlocks(Case_morte(m)),macroMover(MacroMover(m)), pivotHeuristique(isPivotHeuristique)
{

}

AHeuristique::~AHeuristique() {}

