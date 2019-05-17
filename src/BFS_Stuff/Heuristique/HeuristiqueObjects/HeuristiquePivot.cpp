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
HeuristiquePivot::HeuristiquePivot(Maze *m, int coefA, int coefB,GameStat gameStat)
	:AHeuristique(m,coefA,coefB), gameStat(gameStat)
{
	
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
	unsigned short note_caisse_place;
	//[OPTIMIZER]
	//if idealGoal is reach then we pass to the next chapter
 	if ( newPos == node->chapter->getIdealGoalPos()) {
		node->chapter = node->chapter->getNextChapter();
		node->placedBoxes[boxPushedID] = true;

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
* Create and order all the chapters
*
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



