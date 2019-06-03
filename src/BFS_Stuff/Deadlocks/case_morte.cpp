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
	:nb_case_morte(0), m(m)
{
	//ctor
}

Case_morte::~Case_morte()
{
	//dtor
}



/**
* will detect all deadlocks with a BFS system (if a square can not reach a goal with BFS, it is not a deadlocks)
* algo act like if there is no box on the field
*/
void Case_morte::detect_dead_with_BFS_idealGoal(Maze& maze, short idealGoal)
{
	Util u;
	for (unsigned int square = 0; square < maze.getSize(); square++)
	{
		if (!maze.isSquareWall(square) && u.getPathSquareToSquareBM(&maze, square, idealGoal).empty())
		{
			maze.setSquare(square, SPRITE_DEADSQUARE);
		}
	}
}

/**
* will detect all deadlocks with a BFS system (if a square can not reach a goal with BFS, it is not a deadlocks)
* algo act like if there is no box on the field
*/
void Case_morte::detect_dead_with_BFS()
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





/**
* on verifie que l'on ne crée pas une situation de blocage on il serait impossible de bouger des boxes aglomeré entre elle
* on fait un bfs qui va jusqua 2 de prof pour voir si on arrive uniquement à des cas de deadlocks, si c'est le cas on renvoit true
*/
bool Case_morte::detect_dyn_dead_3(unsigned short positionBox, Node *node)
{
	std::unordered_set<short> aglomeratBoxes = u.detectAgglomerateOFBoxes(m, positionBox);
	if (aglomeratBoxes.size() < 2)
		return false;
	bool res = isADynDeadlock(positionBox);
	if (res) {
		return true;
	}
	std::queue<short> toEvaluatate;

	Maze orM(*m);
	bool notDeadLocks = false;
	for (short box : aglomeratBoxes) {
		toEvaluatate.push(box);
	}

	while (!toEvaluatate.empty()) {
		short box = toEvaluatate.front();
		toEvaluatate.pop();
		for (char dir : m->allDirection) {
			short offset = m->getMoveOffset(dir);
			short pusherPlace = box - offset;
			short newBoxPlace = box + offset;
			if (!m->isSquareWalkable(pusherPlace))
				continue;
			if (!m->isSquareDeadSquare(newBoxPlace) && (m->isSquareGround(newBoxPlace) || m->isSquareGoal(newBoxPlace))) {

				m->setPlayerPos(pusherPlace);
				m->updatePlayer(dir);
				std::unordered_set<short> newAglomeratBoxes = u.detectAgglomerateOFBoxes(m, newBoxPlace);
				if (newAglomeratBoxes != aglomeratBoxes) {
					for (short box2 : newAglomeratBoxes)
						if (aglomeratBoxes.find(box2) == aglomeratBoxes.end() && box2 != newBoxPlace) {
							aglomeratBoxes.insert(box2);
							toEvaluatate.push(box2);
						}
				}
				*m = orM;

				if (!isADynDeadlock(newBoxPlace)) {
					notDeadLocks = true;
					return false;
				}

			}
		}
	}

	std::cout << *m;
	knownDealocks.insert(aglomeratBoxes);
	return !notDeadLocks;

}

// return true si l'aglomerat forme une situation de dun deadlock, will also marque countered dynDe	dlox
// work like that:
// calculate if there is a agloremate of Boxes with the bos sent in parameter
// if yes:
//	will elimitate the box that can be mov and will check if some cant be in anycase moved
bool Case_morte::isADynDeadlock(unsigned short positionBox)
{
	std::unordered_set<short> aglomerateBoxes = u.detectAgglomerateOFBoxes(m, positionBox);

	std::unordered_set<short> movableBox;
	std::unordered_set<short> unmovableSet;
	std::unordered_set<short> nextUnmovableSet;

	// si il n'y a pas d'aglomerat de box il n'y a pas de deadlocks dynamique
	if (aglomerateBoxes.size() < 2) {
		return false;
	}

	if (knownDealocks.find(aglomerateBoxes) != knownDealocks.end())
		return true;



	//we marque all box as unmovable
	for (short box : aglomerateBoxes) {
		unmovableSet.insert(box);
	}

	bool movedOne = false;
	do {
		movedOne = false;
		nextUnmovableSet.clear();
		for (short box : unmovableSet) {
			bool isMovableBox = false;
			for (char dir : m->allDirection) {
				short offset = m->getMoveOffset(dir);
				short pusherPlace = box - offset;
				short newBoxPlace = box + offset;
				bool isMovableBoxNeigbourh = movableBox.find(newBoxPlace) != movableBox.end();
				if (!m->isSquareWalkable(pusherPlace))
					continue;
				if (!m->isSquareDeadSquare(newBoxPlace) && (m->isSquareWalkable(newBoxPlace) || isMovableBoxNeigbourh)) {
					isMovableBox = true;
					break;
				}
			}
			if (isMovableBox) {
				movableBox.insert(box);
				movedOne = true;
			}
			else {
				nextUnmovableSet.insert(box);
			}
		}
		unmovableSet = nextUnmovableSet;
	} while (movedOne&&unmovableSet.size() > 0);
	if (unmovableSet.size() == 0) {

		return false;
	}
	else {
		knownDealocks.insert(aglomerateBoxes);
		return true;
	}

}




