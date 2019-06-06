/**
 * \file MacroMover.h
 * \brief declaration of the class MacroMover
 * \author romain michau
 * \version 2.1
 */
#ifndef MACROMOVER_H
#define MACROMOVER_H
#include <utility>
#include <unordered_map>
#include <vector>
#include <unordered_map>
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/Maze/Maze.h"
#include "src/utils/Util.h" 



class MacroMover
{

public:
    MacroMover(Maze* m) :m(m) {};
    std::pair<short, short> macroMovePivotToPoint(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxID);

private:
    std::unordered_map<int, std::vector< Node::NodeRetrackInfo>> savedPath;
    Util u;
    Maze *m;


};
#endif
