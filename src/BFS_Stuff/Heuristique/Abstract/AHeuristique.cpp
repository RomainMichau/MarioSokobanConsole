/**
 * \file AHeurisitique.cpp
 * \brief implementation of the class AHeurisitique
 * \author Romain Michau
 * \version 2.1
 */
#include "AHeuristique.h"
#include <algorithm>

 /** \brief Constructor of the interface AHeuristique
     *
     * \param m: Maze attributed to this class
     * \param coefA: coef used to calculated the note of each Node
     * \param coefB: coef used to calculated the note of each Node
     * \param isPivotHeuristique: true if the interface implement the class HeuristiquePivot
     *
     */
AHeuristique::AHeuristique(Maze *m, int coefA, int coefB,bool isPivotHeuristique) :
    m(m),note(Note(coefA, coefB, 50000)), deadlocks(Case_morte(m)),macroMover(MacroMover(m)), pivotHeuristique(isPivotHeuristique)
{

}
  /** \brief Destructor of the class AHeuristique
     */
AHeuristique::~AHeuristique() {}

