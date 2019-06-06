/**
 * \file AHeurisitique.cpp
 * \brief implementation of the class AHeurisitique
 * \author romain michau
 * \version 2.1
 */
#include "AHeuristique.h"
#include <algorithm>
AHeuristique::AHeuristique(Maze *m, int coefA, int coefB,bool isPivotHeuristique) :
    m(m),note(Note(coefA, coefB, 50000)), deadlocks(Case_morte(m)),macroMover(MacroMover(m)), pivotHeuristique(isPivotHeuristique)
{

}

AHeuristique::~AHeuristique() {}

