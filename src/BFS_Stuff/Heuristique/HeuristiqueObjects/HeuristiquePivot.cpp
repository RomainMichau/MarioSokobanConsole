#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.h"
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
HeuristiquePivot::HeuristiquePivot(Maze *m, int coefA, int coefB)
	:AHeuristique(m,coefA,coefB)
{
	
	calcGameStat();
	chapters = calcChapter();
	this->chapters = chapters;
}

HeuristiquePivot::~HeuristiquePivot()
{
	//dtor
}

/**
* calculate the note of the current state of the field
* will autmaticly set the note in the sent BFSCase
* will also refresh the mapStat of the BFSCase
*/
void HeuristiquePivot::calcHeuristiqueNote(Node *node, short boxPushedID, short newPos)
{
	this->node = node; 
	unsigned short note_caisse_place;
	//[OPTIMIZER]
	//if idealGoal is reach then we pass to the next chapter
 	if ( newPos == this->node->chapter->getIdealGoalPos()) {
		this->node->chapter = this->node->chapter->getNextChapter();
		this->node->placedBoxes[boxPushedID] = true;

	}

	std::vector<unsigned short> box = m->getPosBoxes();
	unsigned short distanecNoteBFS = calc_note_distance_box_bfs_multiple_box();
	//calc_note_distance_box_bfs_multiple_box_new();

	note.set_note_distance_box(distanecNoteBFS);

	//[OPTIMIZER]
	//we add a penalty for each box which is not on a ideal Goal
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
void HeuristiquePivot::calcGameStat() {
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
std::vector<short> HeuristiquePivot::calcMapDistanceFromNearestGoals()
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
std::vector<short> HeuristiquePivot::calcFrequentationSquares()
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
short HeuristiquePivot::calcPivotPointPos(std::vector<short> distMap)
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
Chapter  HeuristiquePivot::calcChapter() {
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



