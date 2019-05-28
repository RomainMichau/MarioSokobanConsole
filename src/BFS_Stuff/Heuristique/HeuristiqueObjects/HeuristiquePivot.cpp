#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiquePivot.h"
#include "src/Maze/Maze.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Chapter.h"
#include "src/BFS_Stuff/Heuristique/MacroMover/MacroMover.h"
#include <utility>

#include <cmath>
#include <math.h>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>
HeuristiquePivot::HeuristiquePivot(Maze *m, int coefA, int coefB, GameStat gameStat)
	:AHeuristique(m, coefA, coefB, true), gameStat(gameStat)
{

	chapters = calcChapter();
	this->chapters = chapters;
	nb_caisse_place_best = 0;
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
	if (newPos == node->chapter->getIdealGoalPos())
	{
		node->chapter = node->chapter->getNextChapter();
		node->placedBoxes[boxPushedID] = true;

	}


	std::vector<unsigned short> box = m->getPosBoxes();
	unsigned short distanecNoteBFS = calc_note_distance_box_pivot();
	note.set_note_distance_box(distanecNoteBFS);


	//[OPTIMIZER]
	//we add a penalty for each box which is not on a ideal Goal
	note_caisse_place = 0;
	int nb_caisse_place = 0;
	for (unsigned int i = 0; i < box.size(); i++)
	{
		if (!node->placedBoxes[i])
			note_caisse_place += 1000;
		else
		{
			nb_caisse_place++;
		}
	}


	if (nb_caisse_place > nb_caisse_place_best) {
		nb_caisse_place_best = nb_caisse_place;
		std::cout << *m << std::endl << "casse placé: " << nb_caisse_place << std::endl;
	}/*
	if (nb_caisse_place == 6) {
		std::cout << *m << std::endl << "casse placé: " << nb_caisse_place << std::endl;
		system("pause");
	}
	if (nb_caisse_place_best >= 6)
		std::cout << *m << std::endl << "casse placé: " << nb_caisse_place << std::endl;
		*/
	note.set_note_caisse_place(note_caisse_place);
	note.calculTotal();
	node->note = note;
}

std::pair<short, short>HeuristiquePivot::macroMove(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxPosition)
{
	if (boxPosition == this->gameStat.getPivotPointPos())
		return 	macroMover.macroMovePivotToPoint(caseTracker, node, boxPosition);

	return std::pair<short, short>(-1, -1);
}

/**
* Create and order all the chapters
* IdealGoal is the farest empty goal from the pivot point
*/
Chapter  HeuristiquePivot::calcChapter()
{
	std::vector<Chapter*> res;
	std::vector<unsigned short> goals = m->getGoals();
	for (short i = 0; i < goals.size(); i++)
	{
		short posGOal = goals[i];
		std::vector<short> distMap = u.getDistMapOfSquare(m, posGOal);

		res.push_back(new Chapter(i, goals[i], distMap, i, distMap[this->gameStat.getPivotPointPos()]));
	}
	std::sort(res.begin(), res.end(),
		[](Chapter const *a, Chapter const *b)->
		bool
	{
		return a->getDistPivotGoal() > b->getDistPivotGoal();
	}
	);
	int i = 0;
	Chapter *lastChatper;
	for (Chapter *c : res)
	{
		if (i > 0)
			lastChatper->setNextChapter(c);
		c->setIndex(i);
		i++;
		lastChatper = c;
	}
	return *res[0];
}

/**
* calcul la sommes des distance entre caisse et pivot avec la dist map du GameStat
*/
unsigned short HeuristiquePivot::calc_note_distance_box_pivot() {
	std::vector<unsigned short> boxes = m->getPosBoxes();
	std::vector<unsigned short> distances;
	for (unsigned int box = 0; box < boxes.size(); box++)                                         ////////////Calcul note distance des box
	{
		short dist = 0;
		if (!(m->isSquareBoxPlaced(boxes[box]) || boxes[box] == gameStat.getPivotPointPos()))
		{
			dist = gameStat.getDistFromPivotPoint(boxes[box]);
		}
		distances.push_back(dist);
	}
	short somme = 0;
	std::sort(distances.begin(), distances.end());
	for (unsigned int i = 0; i < distances.size(); i++)
	{
		somme = somme + (distances[i] * (distances.size() - i));
	}
	return somme;
}
