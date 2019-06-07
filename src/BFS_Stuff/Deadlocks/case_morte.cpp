/**
 * \file case_morte.cpp
 * \brief implementation of the class case_morte
 * \author Romain Michau
 * \version 2.1
 */
#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include <fstream>
#include <iomanip>
#include <queue>
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include <unordered_set>
#include <unordered_map>
#include "src/utils/Util.h"

Case_morte::Case_morte(Maze *m)
    : m(m)
{
}

Case_morte::~Case_morte()
{
}


/** \brief Will detect static DL
*
*  Will make a BFS for each square. If it cant reach a goal, then is it a DL
*  Will marque DL directly on the Maze
*
*/
void Case_morte::detect_static_DL()
{
    Util u;
    for (unsigned int square = 0; square < m->getSize(); square++)
    {
        if (!m->isSquareWall(square) && !m->isSquareGoal(square) && u.getPathSquareToGoalBM(m, square).empty())
        {
            m->setSquare(square, SPRITE_DEADSQUARE);
        }
    }
}





 /** \brief Will detect dynamique Deadlocks on a Node
     *
     * Will also check if the current Node can only lead to other DL
     * Will marque new encoutterd DL
     * \param node: Node to work on
     * \return true if this is a DL
     *
     */
bool Case_morte::detect_dyn_DL(Node *node)
{
    std::unordered_set<unsigned short> aglomeratBoxes = node->aglomeratBoxes;
    if (aglomeratBoxes.size() < 2)
        return false;
    bool res = isADynDeadlock(aglomeratBoxes);
    if (res)
    {
        return true;
    }
    std::queue<short> toEvaluatate;

    //on fait une copy du maze dans son état initial
    Maze orM(*m);
    Maze onlyAglomerateBoxM(*m);
    onlyAglomerateBoxM.setPosBoxes(aglomeratBoxes);
    *m = onlyAglomerateBoxM;
    short normPos;
    std::vector<bool> zoneAccess = u.calcZoneAccessible(&onlyAglomerateBoxM, normPos);

    bool notDeadLocks = false;
    for (short box : aglomeratBoxes)
    {
        toEvaluatate.push(box);
    }

    //on essaye tout les mouvement possible sur les differentes box de l'agglomereat
    // si il mene tous vers des deadlocks, alors il s'agit d'un cas de deadlocks
    while (!toEvaluatate.empty())
    {
        short box = toEvaluatate.front();
        toEvaluatate.pop();
        for (char dir : m->allDirection)
        {
            short offset = m->getMoveOffset(dir);
            short pusherPlace = box - offset;
            short newBoxPlace = box + offset;
            if (!m->isSquareWalkable(pusherPlace) || !zoneAccess[pusherPlace])
                continue;
            if (!m->isSquareDeadSquare(newBoxPlace) && (m->isSquareGround(newBoxPlace) || m->isSquareGoal(newBoxPlace)))
            {

                m->setPlayerPos(pusherPlace);
                m->updatePlayer(dir);
                std::unordered_set<unsigned short> newAglomeratBoxes = u.detectAgglomerateOFBoxes(m, newBoxPlace);
                if (!isADynDeadlock(newAglomeratBoxes))
                {
                    notDeadLocks = true;
                    *m = orM;
                    return false;
                }
                *m = onlyAglomerateBoxM;


            }
        }
    }
    *m = orM;
    knownDealocks.insert(aglomeratBoxes);
    return !notDeadLocks;
}

 /** \brief Check if the node is marque as a DL
     *
     * \param node: node to check
     * \return true if it is marque as a DL
     *
     */
bool Case_morte::isMarqueAsDL(Node * node)
{
    return knownDealocks.find(node->aglomeratBoxes) != knownDealocks.end();
}

/** \brief Detect if an aglomerate is a DL
     *
     * \param aglomerateBoxes aglomareate to check
     * \return true if it is a DL
     *
     */
bool Case_morte::isADynDeadlock(std::unordered_set<unsigned short> aglomerateBoxes)
{

    std::unordered_set<short> movableBox;
    std::unordered_set<short> unmovableSet;
    std::unordered_set<short> nextUnmovableSet;

    // si il n'y a pas d'aglomerat de box il n'y a pas de deadlocks dynamique
    if (aglomerateBoxes.size() < 2)
    {
        return false;
    }

    if (knownDealocks.find(aglomerateBoxes) != knownDealocks.end())
        return true;



    //we marque all box as unmovable
    for (unsigned short box : aglomerateBoxes)
    {
        unmovableSet.insert(box);
    }

    bool movedOne = false;
    do
    {
        movedOne = false;
        nextUnmovableSet.clear();
        for (short box : unmovableSet)
        {
            bool isMovableBox = false;
            for (char dir : m->allDirection)
            {
                short offset = m->getMoveOffset(dir);
                short pusherPlace = box - offset;
                short newBoxPlace = box + offset;
                bool isMovableBoxNeigbourh = movableBox.find(newBoxPlace) != movableBox.end();
                if (!m->isSquareWalkable(pusherPlace))
                    continue;
                if (!m->isSquareDeadSquare(newBoxPlace) && (m->isSquareWalkable(newBoxPlace) || isMovableBoxNeigbourh))
                {
                    isMovableBox = true;
                    break;
                }
            }
            if (isMovableBox)
            {
                movableBox.insert(box);
                movedOne = true;
            }
            else
            {
                nextUnmovableSet.insert(box);
            }
        }
        unmovableSet = nextUnmovableSet;
    }
    while (movedOne&&unmovableSet.size() > 0);
    if (unmovableSet.size() == 0)
    {
        return false;
    }
    else
    {

        knownDealocks.insert(aglomerateBoxes);
        return true;
    }

}




