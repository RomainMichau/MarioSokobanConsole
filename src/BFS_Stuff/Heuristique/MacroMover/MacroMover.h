/**
 * \file MacroMover.h
 * \brief declaration of the class MacroMover
 * \author Romain Michau
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


/** \class MacroMover
 * \brief class used for doing some macro move
 *
 */
class MacroMover
{

private:

    /**
     *  map{goal to reach=>path to take for reach ideal goal from pivot point}
     *  is filled during the resolution of the game
     */
    std::unordered_map<int, std::vector< Node::NodeRetrackInfo>> savedPath;
    Util u;/**< Util */
    Maze *m;/**< Maze */
public:
    /** \brief Constructor of the class MacroMover
     *
     * \param m: Maze
     */
    MacroMover(Maze* m) :m(m) {};


    /** \brief Will add some NodeRetrackInfo in the Node Vector for creating a macro Move
     *
     *  Will create a macro Move beetween the current box position and the ideal goal of the node
     *
     * Will generaly be called when a box reach the pivot point
     * \param caseTracker: NodeRetrackInfo vector (will be alterated)
     * \param node: current node
     * \param boxID: id of the moved box
     * \return {player_pos, box pos} after moves if a way is find else : {-2,-2}
     *
     */
    std::pair<short, short> macroMoveBoxToIdealGoal(std::vector<Node::NodeRetrackInfo>&caseTracker, const Node *node, const short boxID);
};
#endif
