#ifndef NODE_H
#define NODE_H
/**
 * \file Node.h
 * \brief declaration of the class Node
 * \author Romain Michau
 * \version 2.1
 */
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.h"
#include "src/BFS_Stuff/BFS_Objects/Chapter.h"
#include "src/Maze/GameState.h"

#include <unordered_set>

/** \class Node
* \brief Represent a Node of the BFS used in BFSPLUS
* This class represent a Node of the bfs.
* For this BFS a Node represent the movement of a box beetween two linked square
* It has all the informations needed for recreate the state game corresponding to this node
*/
class Node
{




public:

    /** \class NodeRetrackInfo
    * \brief Contains info needed for retracking
    *
    * Inherit of NodeCaseMother (for id informations)
    * this nested class contains some specifics information about this BFSCase
    * it is used for retrack the path at the end of the BFS
    */
    class NodeRetrackInfo : public NodeCaseMother
    {
    public:

        /** \brief Constructor of NodeRetrackInfo
         *
         * \param id: id of this Node
         * \param idParent: id of the Node which created  the current Node
         * \param playerPosBeforeMove: position of the player before the move corresponding to this node
         * \param playerPosAfterMove: position of the player after the move corresponding to this node
         *
         */
        NodeRetrackInfo	(int id, int idParent, short playerPosBeforeMove, short playerPosAfterMove)
            : NodeCaseMother(id, idParent),playerPosBeforeMove(playerPosBeforeMove), playerPosAfterMove(playerPosAfterMove)
        {
        };

        /** \brief Default Constructor of NodeRetrackInfo
         *   Will give default values to attribut
         */
        NodeRetrackInfo() :NodeCaseMother(-1, -1),playerPosBeforeMove(-1), playerPosAfterMove(-1) {};


        /** \brief Destructor of NodeRetrackInfo
         *
         *
         */
        ~NodeRetrackInfo() {};

        short  playerPosBeforeMove;/**< position of the player before the move corresponding to this node */
        short  playerPosAfterMove;/**< position of the player after the move corresponding to this node */
    };

public:
    std::vector<bool> accessibleZone;/**< accessible zone ongoing during this Node */
    GameState gameState;/**< GameState ongoing during this node */
    std::vector<bool> placedBoxes;/**< a vector wich represent which boxes is placed on its ideal Goals : placedBoxes[i]==true if box i is on an ideal goal */
    Note note; /**< Note of this node */
    std::unordered_set<unsigned short> aglomeratBoxes;/**< alomerat of boxes created by the movement of this node */
    unsigned short  depht; /**<  depht of this node */
    Chapter *chapter;/**<  chapter ongoing during this Node */
    NodeRetrackInfo  bfsRetrack;/**< NodeRetrackInfo of this node */

    public:
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
     */
    Node( Chapter *chapter, std::vector<bool> accessibleZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes, unsigned short  depht, NodeRetrackInfo bfsR, short nbBoxes);

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
    Node( Chapter *chapter, std::vector<bool> accessibleZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes,unsigned short  depht, NodeRetrackInfo bfsR, std::vector<bool> placedBoxes);


    /** \brief Destructor of the class Node
     *
     */
    ~Node() {};

};
#endif
