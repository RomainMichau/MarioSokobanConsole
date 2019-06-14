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
#include "src/BFS_Stuff/Deadlocks/DeadlocksObjects/DynDeadLocks.h"

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
	 *
     * Will  check if the current Node can only lead to other DL
     * Will marque new encoutterd DL
     * \param node: Node to work on
     * \return true if this is a DL
	 *
     *	Method:
	 *		
	 *		-push all boxes which are part of the aglomerate in a queue	\n
	 *		-for each box of the queue, try to move in all  of the 4 direction
	 *		-if each one of this move create a DL or if no move is possible, then the Node is a DL itself
	 *
     */
bool Case_morte::detect_dyn_DL(Node *node)
{
    std::unordered_set<unsigned short> aglomeratBoxes = node->aglomeratBoxes;
    if (aglomeratBoxes.size() < 2)
        return false;
    bool res = isADynDeadlock(m,aglomeratBoxes,node->accessZone.getNPos());
	if (res)
		return true;
    std::queue<short> toEvaluatate;

    //on fait une copy du maze dans son état initial
    Maze orM(*m);
    Maze onlyAglomerateBoxM(*m);
    onlyAglomerateBoxM.setPosBoxes(aglomeratBoxes);
    *m = onlyAglomerateBoxM;
    short normPos;
	AccessZone zoneAccess = u.calcZoneAccessible(&onlyAglomerateBoxM);
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
            if (!m->isSquareWalkable(pusherPlace) || !zoneAccess.isAccessible(pusherPlace))
                continue;
            if (!m->isSquareDeadSquare(newBoxPlace) && (m->isSquareGround(newBoxPlace) || m->isSquareGoal(newBoxPlace)))
            {
                m->setPlayerPos(pusherPlace);
                m->updatePlayer(dir);
                std::unordered_set<unsigned short> newAglomeratBoxes = u.detectAgglomerateOFBoxes(m, newBoxPlace,1);
                if (!isADynDeadlock(m,newAglomeratBoxes,node->accessZone.getNPos()))
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
    knownDealocks.insert(DynDeadLocks(aglomeratBoxes, node->accessZone.getNPos()));
	return true;
}

 /** \brief Check if the node is marque as a DL
     *
     * \param node: node to check
     * \return true if it is marque as a DL
     *
     */
bool Case_morte::isMarqueAsDL(Node * node)
{
    return knownDealocks.find(DynDeadLocks(node->aglomeratBoxes,node->accessZone.getNPos())) != knownDealocks.end();
}

/** \brief Detect if an aglomerate is a DL
     *
     * \param aglomerateBoxes aglomareate to check
     * \return true if it is a DL
     *
	 *	Method:
	*		-Will check if the aglomerate is already known, if yes return true (s0)
	 *		-Will only take in account box which make part of the aglomerat sent in parameters (s1)
	 *		-Will remove all movable box from the aglomerate (recursively)	(s2)
	 *		-If some box are still unmovable, then it is a deadlocks => return true	(s3)
	 *
     */
bool Case_morte::isADynDeadlock(Maze* m, std::unordered_set<unsigned short> aglomerateBoxes,short nPos)
{
    std::unordered_set<short> movableBox;
    std::unordered_set<short> unmovableSet;
    std::unordered_set<short> nextUnmovableSet;

    // si il n'y a pas d'aglomerat de box il n'y a pas de deadlocks dynamique
    if (aglomerateBoxes.size() < 2)
    {
        return false;
    }

	//S0
    if (knownDealocks.find(DynDeadLocks( aglomerateBoxes,nPos)) != knownDealocks.end())
        return true;



    //we marque all box as unmovable
	// S1:
    for (unsigned short box : aglomerateBoxes)
    {
        unmovableSet.insert(box);
    }

	//S2:
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

	//S3:
    if (unmovableSet.size() == 0)
    {
        return false;
    }
    else
    {

        knownDealocks.insert(DynDeadLocks(aglomerateBoxes,nPos));
        return true;
    }

}




