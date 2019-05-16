#include "HeuristiqueClassique.h"

HeuristiqueClassique::HeuristiqueClassique(Maze * m, int coefA, int coefB)
	:AHeuristique(m, coefA,coefB) 
{
}

HeuristiqueClassique::~HeuristiqueClassique()
{
}


void HeuristiqueClassique::calcHeuristiqueNote(Node *node, short boxPushedID, short newPos) {

	
	std::vector<unsigned short> box = m->getPosBoxes();
	unsigned short distanecNoteBFS = calc_note_distance_box_bfs_multiple_box();

	note.set_note_distance_box(distanecNoteBFS);

	//[OPTIMIZER]
	//we add a penalty for each box which is not on a ideal Goal
	short note_caisse_place = 0;
	for (unsigned int i = 0; i < box.size(); i++)
	{
		short pos = box[i];
		if (!m->isSquareBoxPlaced(pos))
			note_caisse_place++;
	}
	note.set_note_caisse_place(note_caisse_place);
	note.calculTotal();
	node->note = note;
}
