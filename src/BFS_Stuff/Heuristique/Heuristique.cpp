#include "src/BFS_Stuff/Heuristique/Heuristique.h"
#include "src/Maze/Maze.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Chapter.h"

#include <cmath>
#include <math.h>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>
Heuristique::Heuristique(Maze *m, int coefA, int coefB)
	:m(m), note(Note(coefA, coefB, 50000)), deadlocks(Case_morte(m))
{
	calcGameStat();
	chapters = calcChapter();
	this->chapters = chapters;
}

Heuristique::~Heuristique()
{
	//dtor
}


/**
* calculate the note of the current state of the field
* will autmaticly set the note in the sent BFSCase
* will also refresh the mapStat of the BFSCase
*/
void Heuristique::calcHeuristiqueNote(Node *node, short boxPushedID, short newPos)
{
	this->node = node;
	unsigned short note_caisse_place;
	if (newPos == this->node->chapter->getIdealGoalPos()) {
		this->node->chapter = this->node->chapter->getNextChapter();
		this->node->placedBoxes[boxPushedID] = true;

	}

	std::vector<unsigned short> box = m->getPosBoxes();
	unsigned short distanecNoteBFS = calc_note_distance_box_bfs_multiple_box();
	//calc_note_distance_box_bfs_multiple_box_new();

	note.set_note_distance_box(distanecNoteBFS);

	note_caisse_place = 0;
	for (unsigned int i = 0; i < box.size(); i++)
	{
		if (!node->placedBoxes[i])
			note_caisse_place += 1;
	}
	note.set_note_caisse_place(note_caisse_place);
	note.calculTotal();
	node->note = note;
}


/**
* will calculate the GameSTate of the current Game (*m)
*/
void Heuristique::calcGameStat() {
	// calculatiing and setting frequentationMap
	std::vector<short> freqMap = calcFrequentationSquares();
	this->gameStat.setMapFrequentationSquares(freqMap);

	// get an estimation of the distance beetween all the squares and goals
	std::vector<short> distanceMap = calcMapDistanceFromNearestGoals();

	// with the distance map and the previously calculated frequentation map, we calculate the piovtPoint
	short posPivotPointPos = calcPivotPointPos(distanceMap);
	this->gameStat.setPivotPoint(posPivotPointPos);
}





/**
* for each square calculate the distance with the nearest goal
*/
std::vector<short> Heuristique::calcMapDistanceFromNearestGoals()
{
	Util u;
	std::vector<short> res;
	std::vector<unsigned char> field = m->getField();
	for (unsigned square = 0; square < m->getField().size(); square++)
	{
		if (m->isSquareWall(square) || m->isSquareDeadSquare(square))
		{
			res.push_back(-1);
			continue;
		}
		unsigned size = u.getPathSquareToGoalPBM(m, square).size();
		res.push_back(size);
	}
	return res;
}



/**
* return a vector of the size of the field
* for each box we calculate the path to go to the goal
* each square is represented by the number of box wich have run on it
*
*/
std::vector<short> Heuristique::calcFrequentationSquares()
{
	std::vector<short> res;
	res.resize(m->getField().size(), 0);
	std::vector<unsigned char> field = m->getField();
	for (int box : m->getPosBoxes())
	{

		std::deque<short> path = u.getPathSquareToGoalPBM(m, box);

		//the last element is the goal himself, so we remove him
		if (path.size() > 0)
		{
			path.pop_back();
		}
		for (short sq : path)
		{
			res[sq]++;
		}
	}
	return res;
}

/**
* return the pivot point of mapStat
* definit of pivotPoint: the point with the most frequentation.
* if there is many point with the same max frequentation, then the farest from the goal win
* @see MapStat
* REQUIREMENT: the mapStat of the Heursitque class must have:*
*	-a distMap defined (with method calcMapDistanceFromIdealGoal or calcMapDistanceFromNearestGoals)
*
*@param: distMap: represent the distance from all the saure to the goal
*/
short Heuristique::calcPivotPointPos(std::vector<short> distMap)
{
	std::vector<short> freqMap = this->gameStat.getMapFrequentationSquares();
	short pivotPoint = -1;
	int mostFreqValue = 0;
	int longestDistance = 0;
	for (unsigned i = 0; i < freqMap.size(); i++)
	{
		short dist = distMap[i];
		short freq = freqMap[i];
		if (freq > mostFreqValue)
		{
			mostFreqValue = freq;
			longestDistance = dist;
			pivotPoint = i;
		}
		else if (freq == mostFreqValue && dist > longestDistance)
		{
			longestDistance = dist;
			pivotPoint = i;
		}
	}
	return pivotPoint;
}




/**
* Create and order all the chapters
*/
Chapter  Heuristique::calcChapter() {
	std::vector<Chapter*> res;
	std::vector<unsigned short> goals = m->getGoals();
	for (short i = 0; i < goals.size(); i++) {
		short posGOal = goals[i];
		std::vector<short> distMap = u.getDistMapOfSquare(m, posGOal);

		res.push_back(new Chapter(i, goals[i], distMap, i, distMap[this->gameStat.getPivotPointPos()]));
	}
	std::sort(res.begin(), res.end(),
		[](Chapter const *a, Chapter const *b)->
		bool {
		return a->getDistPivotGoal() > b->getDistPivotGoal();
	}
	);
	int i = 0;
	Chapter *lastChatper;
	for (Chapter *c : res) {
		if (i > 0)
			lastChatper->setNextChapter(c);
		c->setIndex(i);
		i++;
		lastChatper = c;
	}


	return *res[0];
}


unsigned short Heuristique::calc_note_distance_box_bfs_multiple_box_new() {
	std::vector<unsigned short> boxes = m->getPosBoxes();
	std::vector<unsigned short> goals = m->getGoals();
	short bestdistance;
	unsigned short goalreserve = 0;
	std::vector<unsigned short> pluscourt;
	int somme = 0;

	for (unsigned int box = 0; box < boxes.size(); box++)                                         ////////////Calcul note distance des box
	{

		bestdistance = 10000;
		for (unsigned int goal = 0; goal < goals.size(); goal++)
		{
			if (goals[goal] == 0)
				continue;
			//pluscourt.push_back(u.getPathSquareToSquareMPM(*m, boxes[box], this->node->chapter->getIdealGoalPos()).size());
			short distance = u.getPathSquareToSquareMPM( m, boxes[box], this->node->chapter->getIdealGoalPos()).size();
			if (distance < bestdistance)
			{
				bestdistance = distance;
				goalreserve = goal;
			}

		}	goals[goalreserve] = 0;
		pluscourt.push_back(bestdistance);
	}
	std::sort(pluscourt.begin(), pluscourt.end());
	for (unsigned int i = 0; i < pluscourt.size(); i++)
	{
		somme = somme + (pluscourt[i] * (pluscourt.size() - i));
	}
	return somme;
}

/**
* calcul la sommes des distance entre caisse et goal avec un bfs
*/
unsigned short Heuristique::calc_note_distance_box_bfs_multiple_box()
{
	std::vector<unsigned short> boxes = m->getPosBoxes();
	std::vector<unsigned short> goals = m->getGoals();
	std::queue<unsigned short> queue;
	std::vector<bool> marque;
	bool goalReached = false, instant = false;
	unsigned  somme = 0;
	std::vector<unsigned short> origin;
	unsigned short   position;
	unsigned cpt = 0;
	unsigned short goalreserve = 0, bestdistance;
	std::vector<unsigned short> pluscourt;
	marque.resize(m->getField().size(), false);

	for (unsigned int box = 0; box < boxes.size(); box++)                                         ////////////Calcul note distance des box
	{
		bestdistance = 10000;
		for (unsigned int goal = 0; goal < goals.size(); goal++)
		{
			u.vider(queue);
			cpt = 0;
			if (goals[goal] != 0)
			{
				queue.push(boxes[box]);
				marque[boxes[box]] = true;
				goalReached = false;
				origin.push_back(9999);
				instant = false;
				while (!goalReached)
				{
					if (m->isSquareBoxPlaced(boxes[box]))
					{
						origin.push_back(cpt);
						goalReached = true;
						instant = true;
						break;
					}
					position = queue.front();
					for (char dir : m->allDirection)
					{
						short newPos = position + m->getMoveOffset(dir);

						if (!m->isSquareWall(newPos) && !marque[newPos] && !goalReached && !m->isSquareDeadSquare(newPos))
						{
							if (newPos == goals[goal])
								goalReached = true;
							marque[newPos] = true;
							queue.push(newPos);
							origin.push_back(cpt);
						}
					}
					queue.pop();
					cpt++;
				}
				goalReached = false;
				cpt = origin.size() - 1;
				int distance = 0;
				while (origin[cpt] != 9999)
				{
					distance++;
					cpt = origin[cpt];
				}
				if (instant)
				{
					distance = 0;
					instant = false;
				}
				if (distance < bestdistance)
				{
					bestdistance = distance;
					goalreserve = goal;
				}
				marque.resize(0);
				marque.resize(m->getField().size(), false);
				origin.resize(0);
			}
		}
		goals[goalreserve] = 0;
		pluscourt.push_back(bestdistance);
	}

	std::sort(pluscourt.begin(), pluscourt.end());
	for (unsigned int i = 0; i < pluscourt.size(); i++)
	{
		somme = somme + (pluscourt[i] * (pluscourt.size() - i));
	}
	return somme;
}

/**
* calculate the distance note with the help of the distMap of the current BFSCase
* formule of the note is:
* nearestBoxDist /(nbOfBox - 0) +  2ndNearestBoxDist /(nbOfBox -1) ...
*//*/
unsigned short Heuristique::calc_note_distance_with_distMap() {
	std::vector<short> boxesDistFromidealGoal;
	int i = 0;
	for (short boxPos : m->getPosBoxes()) {
		if (node->nodeStat.isBoxPlaceOnIdealGoal(i)) {
			boxesDistFromidealGoal.push_back(0);
			continue;
		}
		boxesDistFromidealGoal.push_back(node->nodeStat.getMapDistanceFromGoal()[boxPos]);
		i++;
	}
	std::sort(boxesDistFromidealGoal.begin(), boxesDistFromidealGoal.end());
	unsigned short somme = 0;
	for (unsigned int i = 0; i < boxesDistFromidealGoal.size(); i++)
	{
		somme = somme + (boxesDistFromidealGoal[i] * (boxesDistFromidealGoal.size() - i));
	}
	return somme;
}*/

