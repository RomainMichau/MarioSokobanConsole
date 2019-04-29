#include "BFSPLUS.h"
#include "maze.h"
#include "heuristique.h"
#include "util.h"
#include "case_morte.h"
#include <vector>
BFSPLUS::BFSPLUS()
{
	//ctor
}

BFSPLUS::~BFSPLUS()
{
	//dtor
}

void BFSPLUS::reinit()
{
	util u;
	resolution.resize(0);
	chemin.resize(0);

	marque_field.resize(0);
	origin.resize(0);

}

/**
* modified BFS using heureting
*/
std::vector<unsigned char> BFSPLUS::bfs_malin(Maze m, bool dynDeadLocks, int &noeudvisite, int noteA, int noteB, int plafond)  //plafond: nombre de noeud max a explor� avant abandon
{
	std::vector<unsigned short>  vec;
	std::vector<bool> zone_accessible;
	std::vector<bool> new_zone_accessible;
	heuristique h;
	int position_player_or = m.getPosPlayer();
	int a = 0;
	int b = 0;
	int cpt = 0;
	int classement = 0;
	util u;
	unsigned short newPositionOfBox, rang = 0, pos_originel = m.getPosPlayer();
	Note note;
	bool stop_urgent = false;
	int num_position = 0;
	std::vector<unsigned char> field = m.getField(), field_originel = m.getField();
	std::vector<unsigned short> posBoxes = m.getPosBoxes();
	bool win = false;
	unsigned position;
	std::vector<bool> zone_originel = u.zone_accessible(m);
	note =h.heuristiquemaline(m, noteA, noteB, -1);
	
	unsigned profondeur;
	marque_field.push_back(field);

	origin.resize(2);
	case_morte dead;
	origin[0] = 0;
	origin[1] = 4444;
	unsigned short poto = 0;
	std::priority_queue<BFSPLUSCase, std::vector<BFSPLUSCase>, BestBFSCase> queue;
	BFSPLUSCase initCase(zone_originel, m.getField(), note, 0, 0);
	queue.push(initCase);


	while (!win && !queue.empty() && !stop_urgent)
	{
		poto++;

		if (marque_field.size() > plafond)
		{
			noeudvisite = 666666;
			return chemin;
		}


		BFSPLUSCase currentCase = queue.top();
		queue.pop();

		profondeur = currentCase.profondeur;
		field = currentCase.field;
		zone_accessible = currentCase.accessibleZone;
		classement = currentCase.classement;

		m.change_etat_jeu(field, zone_accessible);
		posBoxes = m.getPosBoxes();

		/*
		*/
		for (int boxID = 0; boxID < m.getPosBoxes().size(); boxID++)
		{

			/**
			we look for pushed all boxes in all directions possibles
			*/
			for (char direction : m.allDirection) {
				short offset = m.getMoveOffset(direction);
				//position of the box
				short posBox = posBoxes[boxID];
				//position of the player for push the box
				short pusherPlace = posBox - offset;
				//position of th ebox after pushing it
				short newPosBox = posBox + offset;
				std::vector<char> adjDir = m.getAdjacentDirection(direction);


				//We look if the current box can be pushed in the direction 
				if (!win&&zone_accessible[pusherPlace] && (m._canPushBox(posBox, direction, newPositionOfBox) && !m.isSquareDeadSquare(newPosBox)))
				{
					//If yes we check that it will not create any dynamical deadlocks
					if (dynDeadLocks || !dead.dyn_dead(m, pusherPlace, direction))
					{
						//We put the player a the place for pushing the box
						m.setPlayerPos(pusherPlace);

						//we push the box in the wanted direction
						win = m.updatePlayer(direction);

						//we check that we didn't already marque this case
						if (!compare(m.getField()))
						{

							//We estimate if the accessible zone need to be recalculate (if a path path has been open or closed we nn
							if ((m.isSquareWalkable(m.getPosPlayer() + adjDir[0]) && !m.isSquareWalkable(m.getPosPlayer() - offset + adjDir[0])) || //if we open an adj path
								(m.isSquareWalkable(m.getPosPlayer() + adjDir[1]) && !m.isSquareWalkable(m.getPosPlayer() - offset - adjDir[1]) ////if we open an adj path
									) || (!m.isSquareWalkable(m.getPosPlayer() + adjDir[0]) && m.isSquareWalkable(m.getPosPlayer() + offset + adjDir[0])) //if we close an adj path
								|| (!m.isSquareWalkable(m.getPosPlayer() + adjDir[1]) && m.isSquareWalkable(m.getPosPlayer() + adjDir[1] + offset)))
							{
								//It needs to be recalculate
								new_zone_accessible = u.zone_accessible(m);
							}
							else
							{
								//it does not need, we juste have to make few changement
								new_zone_accessible = zone_accessible;
								new_zone_accessible[m.getPosPlayer()] = true;
								new_zone_accessible[m.getPosBoxes()[boxID]] = false;
							}

							///Calcul de l'heuristique
							note = h.heuristiquemaline(m, noteA, noteB, boxID);


							marque_field.push_back(m.getField());
							origin.push_back(classement);
							origin.push_back(posBoxes[boxID] - offset);
							BFSPLUSCase newCase(new_zone_accessible, m.getField(), note, profondeur + 1, origin.size());
							queue.push(newCase);
							origin.push_back(origin.size() - 2);
							origin.push_back(posBoxes[boxID]);

						}
						m.change_etat_jeu(field, zone_accessible);

					}
				}
			}

		}


	}

	if (queue.empty()) {
		std::cout << "empty";
	}

	classement = origin.size() - 2;
	b = 0;

	while (origin[classement + 1] != 4444)
	{
		resolution.push_back(origin[classement + 1]);
		classement = origin[classement];
		b++;
	}

	m.change_etat_jeu(field_originel, zone_originel);

	resolution.push_back(pos_originel);
	invert(resolution);

	resolution = u.relier_point(m, resolution);
	if (!stop_urgent)
		chemin = m.convert(resolution);


	noeudvisite = marque_field.size();
	// std::cout<<"cpt1:"<<AScpt1<<"  cpt2:"<<AScpt2;
	return chemin;
}

void BFSPLUS::invert(std::vector<unsigned short> &vec)
{
	std::vector<unsigned short> vec2;
	vec2 = vec;
	vec.resize(0);
	for (int i = vec2.size() - 1; i >= 0; i = i - 1)
	{
		vec.push_back(vec2[i]);
	}
}


bool BFSPLUS::compare(std::vector<unsigned char> vec)
{
	return marque_field.exist(vec);
}














