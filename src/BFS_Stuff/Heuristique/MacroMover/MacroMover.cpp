#include "src/BFS_Stuff/Heuristique/MacroMover/MacroMover.h"
#include <utility>
#include <vector>
#include <unordered_map>

/**
* Make a automatical move.
* return {player_box, box pos}	after moves
*/
std::pair<short, short>   MacroMover::macroMovePivotToPoint(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxPosition)
{


	 
    short boxGoal = node->chapter->getIdealGoalPos();
    bool alreadySave = true;
    std::vector< Node::NodeRetrackInfo> retrackToGoal;
    if (savedPath.find(boxGoal) == savedPath.end())
        alreadySave = false;

    if (alreadySave)
    {
        retrackToGoal = savedPath[boxGoal];
    }
    else
    {
        retrackToGoal = u.getPathSquareToSquareZoneMethod(m, boxPosition, node->chapter->getIdealGoalPos(), m->getPosPlayer());
        savedPath[boxGoal] = retrackToGoal;
    }
    if (retrackToGoal.size() == 0)
    {
        return std::pair<short, short>(-2, -2);
    }

    int i = 0;
    int nbExistingCase = caseTracker.size();
    for (Node::NodeRetrackInfo node : retrackToGoal)
    {
        node.idCase = nbExistingCase + i;
        node.idParentCase = node.idCase - 1;
        caseTracker.push_back(node);
        i++;
    }
    short posPlay = retrackToGoal.back().playerPosAfterMove;
    return std::pair<short, short>(posPlay, node->chapter->getIdealGoalPos());

}
