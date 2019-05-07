#include "src/BFS_Stuff/Heuristique/Heuristique.h"
#include "src/Maze/Maze.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/Heuristique/note.h"

#include <cmath>
#include <math.h>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>
Heuristique::Heuristique(Maze *m, int coefA, int coefB)
	:m(m), note(Note(coefA, coefB, 50000)),deadlocks(Case_morte(m))
{

}

Heuristique::~Heuristique()
{
	//dtor
}

/**
* will generate a new MapStat

*/
void Heuristique::generateMapStateFromField(BFSCase *bfsCase) {
	this->bfsCase = bfsCase;
	calcMapStat();
}

/**
* calculate the note of the current state of the field
* will autmaticly set the note in the sent BFSCase
* will also refresh the mapStat of the BFSCase
*/
void Heuristique::calcHeuristiqueNote(BFSCase *bfsCase, short boxPushedID, short newPos)
{
	this->bfsCase = bfsCase;
	unsigned short note_caisse_place;
	if (newPos == this->bfsCase->mapStat.getcIdealGoalPos()) {
			this->bfsCase->mapStat.setBoxIsPlaceOnIdealGoal(boxPushedID, true);
		refreshMapStat();
	}

	std::vector<unsigned short> box = m->getPosBoxes();
	//std::vector<unsigned short> pluscourt;
	unsigned short distanecNoteBFS = calc_note_distance_box_bfs_multiple_box();

	//	unsigned short distanecNoteMap = calc_note_distance_with_distMap();
	note.set_note_distance_box(distanecNoteBFS);

	note_caisse_place = 0;
	for (unsigned int i = 0; i < box.size(); i++)
	{
		if (!bfsCase->mapStat.isBoxPlaceOnIdealGoal(i))
			note_caisse_place+=1;
	}
	note.set_note_caisse_place(note_caisse_place);
	note.calculTotal();
	//	calcMapStat();
	bfsCase->note = note;
}

/**
* will refresh the mapState of the current BFSstate with the state of the field
* Method:
*	1) get an estimation of the distance beetween all the squares and goals
*	2) get an estimation of the frequentation map (see definition in MapStat class)
*	3) with this to estimation we can calculate the pivot point
*	4) then we find the ideal goal
*	5) finaly we recaculate the distance map (step 1) but with the idealGoal
*	6) we set all theses values is the mapStat
*/
void Heuristique::calcMapStat() {
	//1) get an estimation of the distance beetween all the squares and goals
	std::vector<short> distanceMap = calcMapDistanceFromNearestGoals();
	//2) get an estimation of the frequentation map(see definition in MapStat class)
	std::vector<short> freqMap = calcFrequentationSquares();
	//set this values in the mapStat
	bfsCase->mapStat.setMapDistanceFromGoal(distanceMap);
	bfsCase->mapStat.setMapFrequentationSquares(freqMap);
	//3) with this to estimation we can calculate the pivot point
	short posPivotPointPos = calcPivotPointPos();
	bfsCase->mapStat.setPivotPoint(posPivotPointPos);
	//4) then we find the ideal goal
	short idealGoalPos = calcIdealGoalPos();
	bfsCase->mapStat.setIdealGoal(idealGoalPos);
	//5) finaly we recaculate the distance map(step 1) but with the idealGoal
	distanceMap = calcMapDistanceFromIdealGoal();
	bfsCase->mapStat.setMapDistanceFromGoal(distanceMap);
	//	u.dispVector(*m,distanceMap);
}

/**
* will refresh the distance and the ideal goal of the curent bfsCase->map stat
*/
void Heuristique::refreshMapStat() {
	//4) then we find the ideal goal
	short idealGoalPos = calcIdealGoalPos();
	bfsCase->mapStat.setIdealGoal(idealGoalPos);
	//5) finaly we recaculate the distance map(step 1) but with the idealGoal
	std::vector<short>	distanceMap = calcMapDistanceFromIdealGoal();
	bfsCase->mapStat.setMapDistanceFromGoal(distanceMap);
	//u.dispVector(*m,distanceMap);
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
		short size = u.getPathSquareToGoal(*m, square).size();
		res.push_back(size);
	}
	return res;
}

/**
* for each square calculate the distance with the nearest goal
*/
std::vector<short> Heuristique::calcMapDistanceFromIdealGoal()
{
	std::vector<short> res;
	std::vector<unsigned char> field = m->getField();
	for (unsigned square = 0; square < m->getField().size(); square++)
	{
		if (square == bfsCase->mapStat.getcIdealGoalPos()) {
			res.push_back(0);
			continue;
		}
		if (m->isSquareWall(square) || m->isSquareDeadSquare(square))
		{
			res.push_back(-1);
			continue;
		}
		short size = u.getPathSquareToSquare(*m, square, bfsCase->mapStat.getcIdealGoalPos()).size();
		size = size == 0 ? -1 : size;
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

		std::deque<short> path = u.getPathSquareToGoal(*m, box);

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
* REQUIREMENT: the mapStat of the Heursitque class must have:
*	-a frequentation map defined (with calcFrequentationSquares)
*	-a distMap defined (with method calcMapDistanceFromIdealGoal or calcMapDistanceFromNearestGoals
*/
short Heuristique::calcPivotPointPos()
{
	std::vector<short> freqMap = this->bfsCase->mapStat.getMapFrequentationSquares();
	std::vector<short> distMap = this->bfsCase->mapStat.getMapDistanceFromGoal();
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
* ideal goal is the goal which is the farest from the pivot point
*/
short Heuristique::calcIdealGoalPos()
{
	std::vector<unsigned short> goals = m->getGoals();
	short pivotpoint = bfsCase->mapStat.getPivotPointPos();
	short longuestDist = 0;
	short idealGoalPos = 0;
	for (unsigned i = 0; i < goals.size(); i++) {
		short pos = goals[i];
		short dist = u.getPathSquareToSquare(*m, pivotpoint, pos).size();
		if (!bfsCase->mapStat.isBoxPlaceOnIdealGoal(i) && dist > longuestDist) {
			idealGoalPos = pos;
			longuestDist=dist;
		}
	}
	return idealGoalPos;
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
	unsigned short somme = 0;
	std::vector<unsigned short> origin;
	unsigned short  cpt = 0, position;
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
*/
unsigned short Heuristique::calc_note_distance_with_distMap() {
	std::vector<short> boxesDistFromidealGoal;
	int i = 0;
	for (short boxPos : m->getPosBoxes()) {
		if (bfsCase->mapStat.isBoxPlaceOnIdealGoal(i)) {
			boxesDistFromidealGoal.push_back(0);
			continue;
		}
		boxesDistFromidealGoal.push_back(bfsCase->mapStat.getMapDistanceFromGoal()[boxPos]);
		i++;
	}
	std::sort(boxesDistFromidealGoal.begin(), boxesDistFromidealGoal.end());
	unsigned short somme = 0;
	for (unsigned int i = 0; i < boxesDistFromidealGoal.size(); i++)
	{
		somme = somme + (boxesDistFromidealGoal[i] * (boxesDistFromidealGoal.size() - i));
	}
	return somme;
}

