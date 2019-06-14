/**
 * \file BFSPLUS.cpp
 * \brief implementation of the class BFSPLUS
 * \author Romain Michau
 * \version 2.1
 */

#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <unordered_set>

#include "BFSPLUS.h"
#include "src/Maze/Maze.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/Maze/GameState.h"
#include "src/BFS_Stuff/BFS_Objects/accessZone.h"

BFSPLUS::BFSPLUS(Maze *m, AHeuristique* heuristique) :
	heuristique(heuristique), m(m), dead(m)
{
}

BFSPLUS:: ~BFSPLUS() {}

/**
* return true if the current boxPos of *m is already marqued
* if it is not the case it wil marque it
*/
bool BFSPLUS::marqued(short normalizePlayerPos)
{
	std::vector<unsigned short> nposBoxes = m->getPosBoxes();
	std::stringstream result;
	nposBoxes.push_back(normalizePlayerPos);
	std::copy(nposBoxes.begin(), nposBoxes.end(), std::ostream_iterator<short>(result, "."));
	std::string hashG = result.str();

	bool marqued = marque.find(hashG) != marque.end();
	if (!marqued)
	{
		marque.insert(hashG);
	}
	return marqued;
}

/**
* modified BFS using heursitic
*/
std::vector<unsigned char> BFSPLUS::runBFS(unsigned &noeudvisite)   //plafond: nombre de noeud max a explor� avant abandon
{
	std::cout << std::endl << heuristique->sayHello() << std::endl;
	GameState orginalGameState = m->getGameState();

	Util u;

	std::vector<unsigned short> resolution;

	std::vector<unsigned char>  field_originel = m->getField();
	std::vector<unsigned short> posBoxes = m->getPosBoxes();
	AccessZone zoneAccessibleOr = u.calcZoneAccessible(m);

	int position_player_or = m->getPosPlayer();
	unsigned short newPositionOfBox, pos_originel = m->getPosPlayer();
	unsigned short profondeur;
	bool win = false;

	marqued(zoneAccessibleOr.getNPos());
	// Vector used for stocking all the bfs state. used for recreatnig the path at the end of the bfs
	std::vector< Node::NodeRetrackInfo>caseTracker;
	std::priority_queue<Node, std::vector<Node>, BestBFSCase> queue;
	Node::NodeRetrackInfo bfsR(0, -1, position_player_or, -1);
	//bfsR.
	Node initCase(heuristique->getChapters(), zoneAccessibleOr, GameState(m->getField(), zoneAccessibleOr.getNPos(), m->getPosBoxes()), std::unordered_set<unsigned short>(), (unsigned short)0, bfsR, m->getPosBoxes().size());
	caseTracker.push_back(bfsR);
	heuristique->calcHeuristiqueNote(&initCase, -1, -1);
	queue.push(initCase);

	while (!win && !queue.empty())
	{
		Node currentCase = queue.top();
		queue.pop();
		//if for any reasons this case ha been marqued has a deadlocks, we skip it
		if (dead.isMarqueAsDL(&currentCase))
			continue;

		profondeur = currentCase.depht;
		GameState currentGameState = currentCase.gameState;		
		AccessZone zone_accessible = currentCase.accessZone;
		/**
		* We set the game in the state
		*/
		m->change_etat_jeu(currentGameState);
		posBoxes = m->getPosBoxes();
		for (unsigned int boxID = 0; boxID < m->getPosBoxes().size(); boxID++)
		{
			//position of the box

			//[OPTIMIZER]
			//si la caisse est deja sur un goal ideal on a pas besoin d'étudier son cas
			//Attention ne marchera pas pour tous les niveau
			if (currentCase.placedBoxes[boxID])
				continue;


			/**
			we look for pushed all boxes in all directions possibles
			*/
			for (char direction : m->allDirection)
			{
				short posBox = posBoxes[boxID];

				short offset = m->getMoveOffset(direction);

				//position of the player for push the box
				short pusherPlace = posBox - offset;
				//position of th ebox after pushing it
				short newPosBox = posBox + offset;

				//We look if the current box can be pushed in the direction
				if (!win&&zone_accessible.isAccessible(pusherPlace) && (m->_canPushBox(posBox, direction, newPositionOfBox) && !m->isSquareDeadSquare(newPosBox)))
				{


					m->setPlayerPos(pusherPlace);

					//we push the box in the wanted direction
					win = m->updatePlayer(direction);

					//[OPTIMIZER TODO]
					//we check that we didn't already marque this case and marqued it if ut is not the case
					//We estimate if the accessible zone need to be recalculate (if a path path h as been open or closed we nn
					AccessZone  new_zone_accessible = u.calcZoneAccessible(m);

					//[OPTIMIZER]
					if (!win && !marqued(new_zone_accessible.getNPos()))
					{
						std::unordered_set<unsigned short>aglomerat = u.detectAgglomerateOFBoxes(m, newPosBox, 1);
						Node::NodeRetrackInfo bfsR(caseTracker.size(), currentCase.bfsRetrack.idCase, posBoxes[boxID] - offset, posBoxes[boxID]);
						Node newCase(currentCase.chapter, new_zone_accessible, GameState(m->getField(), new_zone_accessible.getNPos(), m->getPosBoxes()), aglomerat, profondeur + 1, bfsR, currentCase.placedBoxes);

						//[OPTIMIZER]
						//we check that it will not create any dynamical deadlocks
						// if it is the case we pass to the next Move
						if (dead.detect_dyn_DL(&newCase))
						{
							m->change_etat_jeu(currentGameState);
							continue;
						}
						heuristique->calcHeuristiqueNote(&newCase, boxID, newPosBox);

						caseTracker.push_back(bfsR);

						std::pair<short, short> macroRes = heuristique->macroMove(caseTracker, &newCase, newPosBox);

						if (macroRes.first == -2)
						{
							continue;
						}
						//[OPTIMIZER MACRO]
						else	if (macroRes.first != -1)
						{

							short	boxAfterMacro = macroRes.second;
							short	newPlayerPos = macroRes.first;
							// setting game
							m->setPosBox(boxID, boxAfterMacro);
							m->setPlayerPos(newPlayerPos);
							m->setSquare(boxAfterMacro, SPRITE_BOX_PLACED);
							m->setSquare(newPosBox, field_originel[newPosBox]);
							if (m->_isCompleted())
								win = true;
							AccessZone new_zone_accessibleAfterMacro = u.calcZoneAccessible(m);

							Node::NodeRetrackInfo    bfsMacro = caseTracker.back();
							aglomerat = u.detectAgglomerateOFBoxes(m, boxAfterMacro, 1);
							newCase = Node(currentCase.chapter, new_zone_accessibleAfterMacro, GameState(m->getField(), new_zone_accessibleAfterMacro.getNPos(), m->getPosBoxes()), aglomerat, profondeur + 2, bfsMacro, currentCase.placedBoxes);
							heuristique->calcHeuristiqueNote(&newCase, boxID, boxAfterMacro);

						}


						queue.push(newCase);
					}
					m->change_etat_jeu(currentGameState);

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


	Node::NodeRetrackInfo retrack = caseTracker.back();
	while (retrack.idCase != 0)
	{
		resolution.push_back(retrack.playerPosAfterMove);
		resolution.push_back(retrack.playerPosBeforeMove);
		retrack = caseTracker[retrack.idParentCase];
	}

	//setting back the game in its original field
	m->change_etat_jeu(orginalGameState);

	resolution.push_back(pos_originel);
	std::reverse(resolution.begin(), resolution.end());
	chemin = u.relier_point(*m, resolution);
	for (unsigned short s : resolution)
	{
		std::cout << s << " ";
	}

	noeudvisite = marque.size();
	return chemin;
}

void BFSPLUS::simulateDeadLocks(short nbOfBoxes)
{
	GameState initGameState = m->getGameState();
	//remove all box from field:
	for (short box : m->getPosBoxes())
		m->setSquare(box, SPRITE_GROUND);
	//for(short box=0;)
}

void BFSPLUS::reinitAttribute()
{
	marque = std::unordered_set < std::string>();
}



















