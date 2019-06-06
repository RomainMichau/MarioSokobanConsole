/**
 * \file Node.cpp
 * \brief implementation of the class Node
 * \author romain michau
 * \version 2.1
 */
#include "src/BFS_Stuff/BFS_Objects/Node.h"


Node:: Node(Chapter *chapter, std::vector<bool> accessibleZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes, unsigned short profondeur, NodeRetrackInfo bfsR,short nbOfBoxes) :
    accessibleZone(accessibleZone),gameState(gameState), aglomeratBoxes(aglomeratBoxes),profondeur(profondeur), chapter(chapter), bfsRetrack(bfsR)
{
    placedBoxes.resize(nbOfBoxes, false);
}

Node::Node(Chapter * chapter, std::vector<bool> accessibleZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes, unsigned short profondeur, NodeRetrackInfo bfsR, std::vector<bool> placedBoxes):
    accessibleZone(accessibleZone),gameState(gameState),placedBoxes(placedBoxes), aglomeratBoxes(aglomeratBoxes), profondeur(profondeur), chapter(chapter), bfsRetrack(bfsR)
{
}

