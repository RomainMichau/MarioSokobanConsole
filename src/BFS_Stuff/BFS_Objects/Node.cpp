/**
 * \file Node.cpp
 * \brief implementation of the class Node
 * \author Romain Michau
 * \version 2.1
 */
#include "src/BFS_Stuff/BFS_Objects/Node.h"

/** \brief Constructor of the Class Node
    *
    * \param chapter Chapter*: chapter ongoing during this Node
    * \param accessibleZone std::vector<bool>: accessible zone ongoing during this Node
    * \param gameState GameState: GameState ongoing during this node
    * \param aglomeratBoxes std::unordered_set<unsigned short>: alomerat of boxes created by the movement of this node
    * \param profondeur unsigned short: depht of this node
    * \param bfsR NodeRetrackInfo: NodeRetrackInfo of this node
    * \param nbBoxes short: number of boxes of the maze
    *
    * Initialise the vector placedBoxes
    */
Node:: Node( Chapter *chapter, AccessZone accessZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes, unsigned short  depht, NodeRetrackInfo bfsR,short nbOfBoxes) :
	accessZone(accessZone), gameState(gameState), aglomeratBoxes(aglomeratBoxes), depht( depht), chapter(chapter), bfsRetrack(bfsR)
{
    placedBoxes.resize(nbOfBoxes, false);
}

/** \brief Constructor of the Class Node
     *
     * \param chapter Chapter*: chapter ongoing during this Node
     * \param accessibleZone std::vector<bool>: accessible zone ongoing during this Node
     * \param gameState GameState: GameState ongoing during this node
     * \param aglomeratBoxes std::unordered_set<unsigned short>: alomerat of boxes created by the movement of this node
     * \param profondeur unsigned short: depht of this node
     * \param bfsR NodeRetrackInfo: NodeRetrackInfo of this node
     * \param placedBoxes std::vector<bool> : a vector wich represent which boxes is placed on its ideal Goals
     *
     */
Node::Node( Chapter * chapter, AccessZone accessZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes, unsigned short  depht, NodeRetrackInfo bfsR, std::vector<bool> placedBoxes):
	accessZone(accessZone), gameState(gameState),placedBoxes(placedBoxes), aglomeratBoxes(aglomeratBoxes),  depht( depht), chapter(chapter), bfsRetrack(bfsR)
{
}

