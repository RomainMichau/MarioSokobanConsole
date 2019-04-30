#include "heuristique.h"
#include "maze.h"
#include "util.h"
#include <cmath>
#include <math.h>
#include <queue>
#include <vector>
#include "note.h"
#include <algorithm>
heuristique::heuristique()
{
	//ctor
}

heuristique::~heuristique()
{
	//dtor
}



Note heuristique::heuristiquemaline(Maze m, int coefA, int coefB, int caisse)
{
	util u;


	Note note(coefA, coefB, 50000);
	unsigned short note_caisse_place;

	std::vector<unsigned short> box = m.getPosBoxes();
	std::vector<unsigned short> pluscourt;
	//if(caisse==-1)
	note.set_note_distance_box(note_distance_box_bfs_multiple_box(m));
	/* else
	 note_caisse=note_distance_box_bfs_one_box(m,caisse);*/

	note_caisse_place = 0;
	for (unsigned int i = 0; i < box.size(); i++)
	{
		if (m.isSquareBoxNonPlaced(box[i]))
			note_caisse_place++;
	}
	note.set_note_caisse_place(note_caisse_place);
	note.calculTotal();
	return note;
}


/**
* calcul la sommes des distance entre caisse et goal avec un mahnatan
*/
unsigned short heuristique::note_distance_box_manhatan(Maze m) {
	std::vector<unsigned short> box = m.getPosBoxes();
	std::vector<unsigned short> goal = m.getGoals();
	util u;
	int res = 0;
	std::vector<unsigned short>  posBox = u.doubldim(goal[0], m);
	for (unsigned int i = 0; i < box.size(); i++)                                         ////////////Calcul note distance des box
	{
		res += abs(u.doubldim(box[i], m)[0] - posBox[0]) + abs(u.doubldim(box[i], m)[1] - posBox[1]);
	}
	return res;
}





/**
* calcul la sommes des distance entre caisse et goal avec un bfs
*/
unsigned short heuristique::note_distance_box_bfs_multiple_box(Maze m)
{
	std::vector<unsigned short> boxes = m.getPosBoxes();
	std::vector<unsigned short> goals = m.getGoals();
	std::queue<unsigned short> queue;
	std::vector<bool> marque;
	bool goalReached = false, instant = false;
	util u;
	unsigned short somme=0;
	std::vector<unsigned short> origin;
	unsigned short  cpt = 0, position;
	unsigned short goalreserve = 0, bestdistance;
	std::vector<unsigned short> pluscourt;
	marque.resize(m.getField().size(), false);

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
					if (m.isSquareBoxPlaced(boxes[box]))
					{
						origin.push_back(cpt);
						goalReached = true;
						instant = true;
					}
					position = queue.front();
					for (char dir : m.allDirection) {
						short newPos = position + m.getMoveOffset(dir);

						if (!m.isSquareWall(newPos) && !marque[newPos] && !goalReached && !m.isSquareDeadSquare(newPos))
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
				marque.resize(m.getField().size(), false);
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
* calcul la distance entre une caisse (param) et les goals
*/
unsigned short heuristique::note_distance_box_bfs_one_box(Maze m, int numBox)
{
	std::vector<unsigned short> box = m.getPosBoxes(), vec;
	std::vector<unsigned short> goal = m.getGoals();
	std::queue<unsigned short> file;
	std::vector<bool> marque;
	std::vector<unsigned short> vec2;
	bool alert = false, instant = false;
	util u;
	unsigned short somme, plus_petit, rang_plus_petit = 0;
	std::vector<unsigned short> origin;
	unsigned short v, b = 0, position;
	unsigned short goalreserve = 0, y;
	std::vector<unsigned short> pluscourt;
	marque.resize(m.getField().size(), false);


	y = 10000;
	for (unsigned int a = 0; a < goal.size(); a++)
	{
		u.vider(file);
		b = 0;

		if (goal[a] != 0)
		{
			file.push(box[numBox]);
			marque[box[numBox]] = true;
			alert = false;
			origin.push_back(9999);
			instant = false;
			while (!alert)
			{
				if (m.isSquareBoxPlaced(box[numBox]))
				{
					origin.push_back(b);
					alert = true;
					instant = true;
				}
				position = file.front();

				if (!m.isSquareWall(position + 1) && !marque[position + 1] && !alert && !m.isSquareDeadSquare(position + 1))
				{
					if (position + 1 == goal[a])
						alert = true;
					marque[position + 1] = true;
					file.push(position + 1);
					origin.push_back(b);


				}
				if (!m.isSquareWall(position - 1) && !marque[position - 1] && !alert && !m.isSquareDeadSquare(position - 1))
				{
					if (position - 1 == goal[a])
						alert = true;
					marque[position - 1] = true;
					file.push(position - 1);
					origin.push_back(b);


				}
				if (!m.isSquareWall(position + m.getCol()) && !marque[position + m.getCol()] && !alert && !m.isSquareDeadSquare(position + m.getCol()))
				{
					if (position + m.getCol() == goal[a])
						alert = true;
					marque[position + m.getCol()] = true;
					file.push(position + m.getCol());
					origin.push_back(b);


				}
				if (!m.isSquareWall(position - m.getCol()) && !marque[position - m.getCol()] && !alert && !m.isSquareDeadSquare(position - m.getCol()))
				{
					if (position - m.getCol() == goal[a])
						alert = true;
					marque[position - m.getCol()] = true;
					file.push(position - m.getCol());
					origin.push_back(b);
				}
				file.pop();
				b++;
			}
			v = 0;
			alert = false;
			b = origin.size() - 1;
			while (origin[b] != 9999)
			{
				v++;
				b = origin[b];
			}
			if (instant)
			{
				v = 0;
				instant = false;
			}

			if (v < y)
			{
				y = v;
				goalreserve = a;
			}

			marque.resize(0);
			marque.resize(m.getField().size(), false);
			origin.resize(0);

		}
	}
	goal[goalreserve] = 0;
	pluscourt.push_back(y);

	b = 0;
	somme = 0;
	while (somme != pluscourt.size() * 1000)
	{
		vec.resize(0);
		plus_petit = 999;
		for (unsigned int i = 0; i < pluscourt.size(); i++)
		{
			if (pluscourt[i] < plus_petit)
			{
				plus_petit = pluscourt[i];
				rang_plus_petit = i;
			}
		}
		pluscourt[rang_plus_petit] = 1000;
		vec.push_back(rang_plus_petit);
		vec.push_back(plus_petit);

		vec2.push_back(plus_petit);

		somme = 0;
		for (unsigned int i = 0; i < pluscourt.size(); i++)
			somme += pluscourt[i];
	}
	somme = 0;
	for (unsigned int i = 0; i < vec2.size(); i++)
	{
		somme = somme + (vec2[i] * (vec2.size() - i));
	}
	return somme;
}

/*
* calcul la distance entre les goal et le perso
*/
unsigned short heuristique::note_disance_perso(Maze m)
{
	std::vector<unsigned short> goal = m.getGoals();
	std::queue<unsigned short> file;
	std::vector<bool> marque;
	std::vector<unsigned char> field;
	bool alert = false, instant = false;
	util u;
	u.vider(file);

	unsigned short note_distance_perso;
	std::vector<unsigned short> origin;
	unsigned short v, position, poto = 0;
	std::vector<unsigned short> pluscourt;
	marque.resize(m.getField().size(), false);
	////////////////////////////////////Calcul note du perso
	u.vider(file);
	marque.resize(0);
	origin.resize(0);
	std::vector<unsigned short> marqued, marqueg, marqueb, marqueh;
	marqueb.resize(m.getField().size(), false);
	marqueh.resize(m.getField().size(), false);
	marqued.resize(m.getField().size(), false);
	marqueg.resize(m.getField().size(), false);
	unsigned short note, note2, dernier_moment = 0;;
	marque.resize(m.getField().size(), false);
	alert = false;
	position = m.getPosPlayer();
	marque[position] = true;
	file.push(position);
	origin.push_back(9999);
	v = 0;
	while (!alert && !m._isCompleted())
	{
		position = file.front();
		poto++;
		if (!m.isSquareWall(position + 1) && !marqued[position + 1] && !alert)
		{
			if (m.isSquareBoxNonPlaced(position + 1) && m.isSquareWalkable(position + 2))
			{
				note = note_distance_box_bfs_multiple_box(m);
				field = m.getField();
				m.change_etat_jeu(field, position);
				m.updatePlayer(RIGHT);
				note2 = note_distance_box_bfs_multiple_box(m);
				if (note2 < note)
				{
					alert = true;
				}
				else
				{
					dernier_moment = origin.size();
				}
				m.change_etat_jeu(field, position);
			}

			marqued[position + 1] = true;
			file.push(position + 1);
			origin.push_back(v);

		}
		if (!m.isSquareWall(position - 1) && !marqueg[position - 1] && !alert)
		{
			if (m.isSquareBoxNonPlaced(position - 1) && m.isSquareWalkable(position - 2))
			{
				note = note_distance_box_bfs_multiple_box(m);
				field = m.getField();
				m.change_etat_jeu(field, position);
				m.updatePlayer(LEFT);
				note2 = note_distance_box_bfs_multiple_box(m);
				if (note2 < note)
				{
					alert = true;
				}
				else
				{
					dernier_moment = origin.size();
				}
				m.change_etat_jeu(field, position);
			}
			marqueg[position - 1] = true;
			file.push(position - 1);
			origin.push_back(v);

		}
		if (!m.isSquareWall(position + m.getCol()) && !marqueb[position + m.getCol()] && !alert)
		{
			if (m.isSquareBoxNonPlaced(position + m.getCol()) && m.isSquareWalkable(position + 2 * m.getCol()))
			{
				note = note_distance_box_bfs_multiple_box(m);
				field = m.getField();
				m.change_etat_jeu(field, position);
				m.updatePlayer(BOTTOM);
				note2 = note_distance_box_bfs_multiple_box(m);
				if (note2 < note)
				{
					alert = true;
				}
				else
				{
					dernier_moment = origin.size();
				}
				m.change_etat_jeu(field, position);
			}


			marqueb[position + m.getCol()] = true;
			file.push(position + m.getCol());
			origin.push_back(v);

		}



		if (!m.isSquareWall(position - m.getCol()) && !marqueh[position - m.getCol()] && !alert)
		{
			//std::cout<<std::endl<<"bas "<<position<<std::endl;
			if (m.isSquareBoxNonPlaced(position - m.getCol()) && m.isSquareWalkable(position - 2 * m.getCol()))
			{
				//  std::cout<<std::endl<<"position actuel: "<<position<<std::endl;
				note = note_distance_box_bfs_multiple_box(m);
				field = m.getField();
				m.change_etat_jeu(field, position);
				m.updatePlayer(TOP);
				note2 = note_distance_box_bfs_multiple_box(m);
				if (note2 < note)
				{
					alert = true;
				}
				else
				{
					dernier_moment = origin.size();
				}
				m.change_etat_jeu(field, position);
			}

			marqueh[position - m.getCol()] = true;
			file.push(position - m.getCol());
			origin.push_back(v);

		}
		file.pop();
		v++;
		if (file.empty())
		{
			alert = true;
			instant = true;
			// std::cout<<"oki";
		}


	}
	v = 0;

	poto = origin.size() - 1;
	if (instant)
		poto = dernier_moment;
	while (origin[poto] != 9999)
	{
		v++;
		poto = origin[poto];

	}

	note_distance_perso = v;
	//std::cout<<note_distance_perso<<"-";
	return note_distance_perso;





}



unsigned short heuristique::note_goal_access(Maze m)
{
	std::vector<unsigned short> box = m.getPosBoxes(), vec;
	std::vector<unsigned short> goal = m.getGoals();
	std::queue<unsigned short> file;
	std::vector<bool> marque;
	util u;
	std::vector<unsigned short> origin;
	unsigned short position;
	std::vector<unsigned short> pluscourt;
	marque.resize(m.getField().size(), false);

	bool stop = false;
	unsigned short goal_atteint = 0;
	u.vider(file);  //////////////////////////////VERFI SI GOAL ACCESIBLE
	marque.resize(0);
	marque.resize(m.getField().size(), false);
	position = m.getPosPlayer();
	marque[position] = true;
	file.push(position);



	while (!m._isCompleted() && !stop)
	{
		position = file.front();



		if (!m.isSquareWall(position + 1) && !marque[position + 1] && !stop && !m.isSquareBox(position + 1) && !m.isSquareDeadSquare(position + 1))
		{

			if (m.isSquareGoal(position + 1))
				stop = true;
			marque[position + 1] = true;
			file.push(position + 1);

		}

		if (!m.isSquareWall(position - 1) && !marque[position - 1] && !stop && !m.isSquareBox(position - 1) && !m.isSquareDeadSquare(position - 1))
		{

			if (m.isSquareGoal(position - 1))
				stop = true;
			marque[position - 1] = true;
			file.push(position - 1);

		}


		if (!m.isSquareWall(position + m.getCol()) && !marque[position + m.getCol()] && !stop && !m.isSquareBox(position + m.getCol()) && !m.isSquareDeadSquare(position + m.getCol()))
		{
			if (m.isSquareGoal(position + m.getCol()))
				stop = true;
			marque[position + m.getCol()] = true;
			file.push(position + m.getCol());

		}

		//std::cout<<"caisse:"<<position-m.getCol()<<"tour:"<<cpt<<"-"<<std::endl;


		if (!m.isSquareWall(position - m.getCol()) && !marque[position - m.getCol()] && !stop && !m.isSquareBox(position - m.getCol()) && !m.isSquareDeadSquare(position - m.getCol()))
		{
			//std::cout<<"pos:"<<position-m.getCol()<<"tour:"<<cpt<<"-"<<std::endl;
			if (m.isSquareGoal(position - m.getCol()))
				stop = true;
			marque[position - m.getCol()] = true;
			file.push(position - m.getCol());

		}

		file.pop();
		if (file.empty())
		{
			stop = true;
			goal_atteint = 1;
		}
		//std::cout<<goal_atteint;
		return goal_atteint;
	}
	return 0;
}
