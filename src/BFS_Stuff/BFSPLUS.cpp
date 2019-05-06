#include "BFSPLUS.h"

#include "src/Maze/maze.h"
#include "src/BFS_Stuff/Heuristique/heuristique.h"
#include "src/utils/util.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
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

void BFSPLUS::reinit()
{
	Util u;
	resolution.resize(0);
	chemin.resize(0);


}

bool BFSPLUS::accessZoneChange(char direction)
{
	short offset = m->getMoveOffset(direction);
	std::vector<char> adjDir = m->getAdjacentDirection(direction);

	return ((m->isSquareWalkable(m->getPosPlayer() + adjDir[0]) && !m->isSquareWalkable(m->getPosPlayer() - offset + adjDir[0])) || //if we open an adj path
		(m->isSquareWalkable(m->getPosPlayer() + adjDir[1]) && !m->isSquareWalkable(m->getPosPlayer() - offset - adjDir[1]) ////if we open an adj path
			) || (!m->isSquareWalkable(m->getPosPlayer() + adjDir[0]) && m->isSquareWalkable(m->getPosPlayer() + offset + adjDir[0])) //if we close an adj path
		|| (!m->isSquareWalkable(m->getPosPlayer() + adjDir[1]) && m->isSquareWalkable(m->getPosPlayer() + adjDir[1] + offset)));
}

bool BFSPLUS::isMarqued()
{
	std::vector<unsigned short> nposBoxes = m->getPosBoxes();
	std::stringstream result;
	std::copy(nposBoxes.begin(), nposBoxes.end(), std::ostream_iterator<short>(result, " "));
	std::string hash = result.str();
	bool marqued= marque.find(hash) != marque.end();
	if (!marqued) {
		marque.insert(result.str());
	}
	return marqued;
}

/**
* modified BFS using heureting
*/
std::vector<unsigned char> BFSPLUS::bfs_malin(unsigned &noeudvisite, int noteA, int noteB, int plafond)   //plafond: nombre de noeud max a explor� avant abandon
{
	Util u;
	Heuristique h(m, noteA, noteB);
	case_morte dead(m);
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
	std::stringstream result2;
	std::copy(posBoxes.begin(), posBoxes.end(), std::ostream_iterator<short>(result2, " "));
	marque.insert(result2.str());


	std::vector< BFSCase::BFSCaseInfo>originNew;  //je fais un tableau ou j'alterne la postion precedente et le mouvement
	// necessaire pour arriver a cette nouvelle etat



	std::priority_queue<BFSCase, std::vector<BFSCase>, BestBFSCase> queue;
	BFSCase::BFSCaseInfo bfsR(0,-1,position_player_or,-1);
	//bfsR.
	(0, -1, position_player_or, position_player_or);
	BFSCase initCase(m->getPosBoxes().size(), zone_originel, m->getField(),(unsigned short) 0, bfsR);
	originNew.push_back(bfsR);
	h.generateMapStateFromField(&initCase);
	h.calcHeuristiqueNote(&initCase, -1, -1);
	queue.push(initCase);
	while (!win && !queue.empty())
	{

		if (marque.size() > plafond)
		{
			noeudvisite = 666666;
			return chemin;
		}
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

						//we check that we didn't already marque this case

						if(!isMarqued())
						{
							//We estimate if the accessible zone need to be recalculate (if a path path h as been open or closed we nn
							if (accessZoneChange(direction))
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
							BFSCase::BFSCaseInfo bfsR(originNew.size(), currentCase.bfsRetrack.id, posBoxes[boxID] - offset, posBoxes[boxID]);
							BFSCase newCase(currentCase.mapStat, new_zone_accessible, m->getField(), profondeur + 1, bfsR);
							h.calcHeuristiqueNote(&newCase, boxID, newPosBox);
							queue.push(newCase);
							originNew.push_back(bfsR);

						}
						m->change_etat_jeu(field, zone_accessible);
					}
				}
			}
		}
	}

	//ON recrée le chemin
	if (queue.empty())
	{
		std::cout << "empty";
	}


	BFSCase::BFSCaseInfo retrack = originNew.back();
	while (retrack.id != 0) {
		resolution.push_back(retrack.playerPosAfterMove);
		resolution.push_back(retrack.playerPosBeforeMove);
		retrack = originNew[retrack.idParent];
	}

	//setting back the game in its original field
	m->change_etat_jeu(field_originel, zone_originel);

	resolution.push_back(pos_originel);
	std::reverse(resolution.begin(), resolution.end());
	resolution = u.relier_point(*m, resolution);
	chemin = m->convert(resolution);

	noeudvisite = marque.size();
	// std::cout<<"cpt1:"<<AScpt1<<"  cpt2:"<<AScpt2;
	return chemin;
}



















