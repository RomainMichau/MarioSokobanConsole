#include "BFSPLUS.h"

#include "src/Maze/Maze.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <unordered_set>
#include "src/Maze/GameState.h"


BFSPLUS::BFSPLUS(Maze *m, AHeuristique* heuristique) :
	heuristique(heuristique), m(m)
{
}

BFSPLUS:: ~BFSPLUS() {}







/**
* return true if the current boxPos of *m is already marqued
* if it is not the case it wil marque it
*/
bool BFSPLUS::marqued(short acc)
{
	std::vector<unsigned short> nposBoxes = m->getPosBoxes();
	std::vector<unsigned char> field = m->getField();
	std::stringstream result;
	nposBoxes.push_back(acc);
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
	Case_morte dead(m);
	std::vector<bool> new_zone_accessible;
	short pos_or;
	std::vector<unsigned char>  field_originel = m->getField();
	std::vector<unsigned short> posBoxes = m->getPosBoxes();
	std::vector<bool> zone_originel = u.calcZoneAccessible(m, pos_or);
	//	marque.clear();

	int position_player_or = m->getPosPlayer();
	unsigned short newPositionOfBox, pos_originel = m->getPosPlayer();
	unsigned short profondeur;
	bool win = false;

	marqued(pos_or);
	// Vector used for stocking all the bfs state. used for recreatnig the path at the end of the bfs
	std::vector< Node::NodeRetrackInfo>caseTracker;
	std::priority_queue<Node, std::vector<Node>, BestBFSCase> queue;
	Node::NodeRetrackInfo bfsR(0, -1, position_player_or, -1);
	//bfsR.
	Node initCase(heuristique->getChapters(), zone_originel, GameState(m->getField(), pos_or, m->getPosBoxes()), std::unordered_set<unsigned short>(), (unsigned short)0, bfsR, m->getPosBoxes().size());
	caseTracker.push_back(bfsR);
	heuristique->calcHeuristiqueNote(&initCase, -1, -1);
	queue.push(initCase);

	while (!win && !queue.empty())
	{
		Node currentCase = queue.top();
		queue.pop();
		//if for any reasons this case ha been marqued has a deadlocks, we skip it
		if (dead.isMarqueAsDeadlocks(&currentCase))
			continue;

		profondeur = currentCase.profondeur;
		GameState currentGameState = currentCase.gameState;
		//	field = currentCase.field;
		//	short nPos = currentCase.normalisePos;
		short newNPos;
		std::vector<bool> 	zone_accessible = currentCase.accessibleZone;
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
				if (!win&&zone_accessible[pusherPlace] && (m->_canPushBox(posBox, direction, newPositionOfBox) && !m->isSquareDeadSquare(newPosBox)))
				{


					m->setPlayerPos(pusherPlace);

					//we push the box in the wanted direction
					win = m->updatePlayer(direction);

					//[OPTIMIZER TODO]
					//we check that we didn't already marque this case and marqued it if ut is not the case
					//We estimate if the accessible zone need to be recalculate (if a path path h as been open or closed we nn
					new_zone_accessible = u.calcZoneAccessible(m, newNPos);

					//[OPTIMIZER]
					if (!win && !marqued(newNPos))
					{
						std::unordered_set<unsigned short>aglomerat = u.detectAgglomerateOFBoxes(m, newPosBox);
						Node::NodeRetrackInfo bfsR(caseTracker.size(), currentCase.bfsRetrack.idCase, posBoxes[boxID] - offset, posBoxes[boxID]);
						Node newCase(currentCase.chapter, new_zone_accessible, GameState(m->getField(), newNPos, m->getPosBoxes()), aglomerat, profondeur + 1, bfsR, currentCase.placedBoxes);

						//[OPTIMIZER]
							//we check that it will not create any dynamical deadlocks
							// if it is the case we pass to the next Move
						if (dead.detect_dyn_dead_3(&newCase)) {
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
							new_zone_accessible = u.calcZoneAccessible(m, newNPos);

							bfsR = caseTracker.back();
							aglomerat = u.detectAgglomerateOFBoxes(m, boxAfterMacro);
							newCase = Node(currentCase.chapter, new_zone_accessible, GameState(m->getField(), newNPos, m->getPosBoxes()), aglomerat, profondeur + 2, bfsR, currentCase.placedBoxes);
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
	resolution = u.relier_point(*m, resolution);
	for (unsigned short s : resolution)
	{
		std::cout << s << " ";
	}
	chemin = m->convert(resolution);

	noeudvisite = marque.size();
	return chemin;
}



















