#ifndef NODE_H
#define NODE_H
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.h"
#include "src/BFS_Stuff/BFS_Objects/Chapter.h"
#include "src/Maze/GameState.h"
#include <unordered_set>
class Node
{
public:

    /**
    * this class represent the specific information about the BFSCase
    * it is used for retrack the path at the end of the BFS
    */
    class NodeRetrackInfo : public NodeCaseMother
    {
    public:

        NodeRetrackInfo	(int id, int idParent, short playerPosBeforeMove, int playerPosAfterMove)
            : NodeCaseMother(id, idParent),playerPosBeforeMove(playerPosBeforeMove), playerPosAfterMove(playerPosAfterMove)
        {
        };

        NodeRetrackInfo() :NodeCaseMother(-1, -1) {};
        //ID of the BFSCase
        ~NodeRetrackInfo() {};

        //pos of the player before he pushed the box
        short playerPosBeforeMove;
        //pos of the player after he pushed the box
        short playerPosAfterMove;
    };

    ~Node() {};
    Node(Chapter *chapter, std::vector<bool> accessibleZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes, unsigned short profondeur, NodeRetrackInfo bfsR, short nbBoxes);
    Node(Chapter *chapter, std::vector<bool> accessibleZone, GameState gameState, std::unordered_set<unsigned short> aglomeratBoxes,unsigned short profondeur, NodeRetrackInfo bfsR, std::vector<bool> placedBoxes);

    std::vector<bool> accessibleZone;
	//State of the game at the node
    GameState gameState;
    //true if box with id i is placed on current or past idealGOal
    // placedBoxes[i] =>true
    std::vector<bool> placedBoxes;
	//note of this node
    Note note;
	//Aglomerat of box created by the move of this node
	std::unordered_set<unsigned short> aglomeratBoxes;
    unsigned short profondeur;
    Chapter *chapter;
    NodeRetrackInfo  bfsRetrack;


};
#endif
