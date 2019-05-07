#include "BFSPLUS.h"

#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/Heuristique.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/DeadLocks/Case_morte.h"
#include "src/BFS_Stuff/BFS_Objects/BFSCase.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <unordered_set>



BFSPLUS::BFSPLUS(Maze *m)
{
	this->m = m;
	//ctor

}

BFSPLUS:: ~BFSPLUS() {}



/**
* return true if the mov in the direction sent in parameters is going to change the accesible zone
*/
bool BFSPLUS::hasAccessZoneChange(char direction)
{
	short offset = m->getMoveOffset(direction);
	std::vector<char> adjDir = m->getAdjacentDirection(direction);

	return ((m->isSquareWalkable(m->getPosPlayer() + adjDir[0]) && !m->isSquareWalkable(m->getPosPlayer() - offset + adjDir[0])) || //if we open an adj path
		(m->isSquareWalkable(m->getPosPlayer() + adjDir[1]) && !m->isSquareWalkable(m->getPosPlayer() - offset - adjDir[1]) ////if we open an adj path
			) || (!m->isSquareWalkable(m->getPosPlayer() + adjDir[0]) && m->isSquareWalkable(m->getPosPlayer() + offset + adjDir[0])) //if we close an adj path
		|| (!m->isSquareWalkable(m->getPosPlayer() + adjDir[1]) && m->isSquareWalkable(m->getPosPlayer() + adjDir[1] + offset)));
}

/**
* return true if the current boxPos of *m is already marqued
* if it is not the case it wil marque it
*/
bool BFSPLUS::marqued()
{
	std::vector<unsigned short> nposBoxes = m->getPosBoxes();
	std::stringstream result;
	std::copy(nposBoxes.begin(), nposBoxes.end(), std::ostream_iterator<short>(result, " "));
	std::string hash = result.str();
	bool marqued = marque.find(hash) != marque.end();
	if (!marqued) {
		marque.insert(result.str());
	}
	return marqued;
}

/**
* modified BFS using heursitic
*/
std::vector<unsigned char> BFSPLUS::runBFS(unsigned &noeudvisite, int noteA, int noteB)   //plafond: nombre de noeud max a explor� avant abandon
{
	Util u;
	Heuristique heurisitique(m, noteA, noteB);
	Case_morte dead(m);
	std::vector<bool> zone_accessible;
	std::vector<bool> new_zone_accessible;
	std::vector<unsigned char> field = m->getField(), field_originel = m->getField();
	std::vector<unsigned short> posBoxes = m->getPosBoxes();
	std::vector<bool> zone_originel = u.calcZoneAccessible(*m);
	//	marque.clear();

	int position_player_or = m->getPosPlayer();
	int classement = 0;
	unsigned short newPositionOfBox, pos_originel = m->getPosPlayer();
	unsigned short profondeur;
	bool win = false;

	marqued();
	// Vector used for stocking all the bfs state. used for recreatnig the path at the end of the bfs
	std::vector< BFSCase::BFSCaseInfo>caseTracker;
	std::priority_queue<BFSCase, std::vector<BFSCase>, BestBFSCase> queue;
	BFSCase::BFSCaseInfo bfsR(0, -1, position_player_or, -1);
	//bfsR.
	BFSCase initCase(m->getPosBoxes().size(), zone_originel, m->getField(), (unsigned short)0, bfsR);
	caseTracker.push_back(bfsR);
	heurisitique.generateMapStateFromField(&initCase);
	heurisitique.calcHeuristiqueNote(&initCase, -1, -1);
	queue.push(initCase);
	while (!win && !queue.empty())
	{
		BFSCase currentCase = queue.top();
		queue.pop();
		profondeur = currentCase.profondeur;
		field = currentCase.field;
		zone_accessible = currentCase.accessibleZone;
		/**
		* We set the game in the state
		*/
		m->change_etat_jeu(field, zone_accessible);
		posBoxes = m->getPosBoxes();
		for (int boxID = 0; boxID < m->getPosBoxes().size(); boxID++)
		{
			//si la caisse est deja sur un goal ideal on a pas besoin d'étudier son cas
			//Attention ne marchera pas pour tous les niveau
			if (currentCase.mapStat.isBoxPlaceOnIdealGoal(boxID))
				continue;


			/**
			we look for pushed all boxes in all directions possibles
			*/
			for (char direction : m->allDirection)
			{
				short offset = m->getMoveOffset(direction);
				//position of the box
				short posBox = posBoxes[boxID];
				//position of the player for push the box
				short pusherPlace = posBox - offset;
				//position of th ebox after pushing it
				short newPosBox = posBox + offset;
				std::vector<char> adjDir = m->getAdjacentDirection(direction);

				//We look if the current box can be pushed in the direction
				if (!win&&zone_accessible[pusherPlace] && (m->_canPushBox(posBox, direction, newPositionOfBox) && !m->isSquareDeadSquare(newPosBox)))
				{
					//If yes we check that it will not create any dynamical deadlocks
					if (!dead.detect_dyn_dead(pusherPlace, direction))
					{
						//We put the player a the place for pushing the box
						m->setPlayerPos(pusherPlace);

						//we push the box in the wanted direction
						win = m->updatePlayer(direction);

						//we check that we didn't already marque this case and marqued it if ut is not the case

						if (!marqued())
						{
							//We estimate if the accessible zone need to be recalculate (if a path path h as been open or closed we nn
							if (hasAccessZoneChange(direction))
							{
								//It needs to be recalculate
								new_zone_accessible = u.calcZoneAccessible(*m);
							}
							else
							{
								//it does not need, we juste have to make few changement
								new_zone_accessible = zone_accessible;
								new_zone_accessible[m->getPosPlayer()] = true;
								new_zone_accessible[m->getPosBoxes()[boxID]] = false;
							}

							//Calcul de l'heuristique

							//	marque_field.push_back(m->getField());
							BFSCase::BFSCaseInfo bfsR(caseTracker.size(), currentCase.bfsRetrack.idCase, posBoxes[boxID] - offset, posBoxes[boxID]);
							BFSCase newCase(currentCase.mapStat, new_zone_accessible, m->getField(), profondeur + 1, bfsR);
							heurisitique.calcHeuristiqueNote(&newCase, boxID, newPosBox);
							queue.push(newCase);
							caseTracker.push_back(bfsR);

						}
						m->change_etat_jeu(field, zone_accessible);
					}
				}
			}
		}
	}

	std::vector<unsigned char> chemin;

	//ON recrée le chemin
	if (queue.empty())
	{
		std::cout << "empty";
		return chemin;
	}


	BFSCase::BFSCaseInfo retrack = caseTracker.back();
	while (retrack.idCase != 0) {
		resolution.push_back(retrack.playerPosAfterMove);
		resolution.push_back(retrack.playerPosBeforeMove);
		retrack = caseTracker[retrack.idParentCase];
	}

	//setting back the game in its original field
	m->change_etat_jeu(field_originel, zone_originel);

	resolution.push_back(pos_originel);
	std::reverse(resolution.begin(), resolution.end());
	resolution = u.relier_point(*m, resolution);
	chemin = m->convert(resolution);

	noeudvisite = marque.size();
	return chemin;
}



















