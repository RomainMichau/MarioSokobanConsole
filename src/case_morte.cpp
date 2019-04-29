#include "maze.h"
#include "../utils/console.h"
#include "../utils/coord.h"
#include <fstream>
#include <iomanip>
#include "case_morte.h"

case_morte::case_morte()
	:nb_case_morte(0)
{
	//ctor
}

case_morte::~case_morte()
{
	//dtor
}


/**
 * Detect all the deadlocks of the maze sent in parameters
 * Detection procedure:
 ** First the algorithm detect all the corners of the game.
 ** Then it mark all the square between two corner as deadlocks (see pdf page 12)
 * @param m Maze
 */
void case_morte::detect_dead(Maze &m)
{

	int cote_mur = 0;
	int hauteur_mur = 0;
	int copyDeadLock;
	int evo = 1;
	std::vector<unsigned char> field = m.getField();

	/**
	* Detection of all the corners and marking them as deadlock
	*/

		m.case_morte_activ = true;

		for (int i = 1 + m.getCol(); i < field.size(); i++)
		{
			if (i > 0 && m.isSquareWall(i - 1))
			{
				cote_mur++;
			}
			if (m.isSquareWall(i - m.getCol()))
			{
				hauteur_mur++;
			}

			if (i + m.getCol() < m.getSize() && m.isSquareWall(i + m.getCol()))
			{
				hauteur_mur++;

			}
			if (i + 1 < m.getSize() && m.isSquareWall(i + 1))
			{
				cote_mur++;

			}
			if (cote_mur >= 1 && hauteur_mur >= 1)
			{
				if (field[i] != SPRITE_WALL && field[i] != SPRITE_DEADSQUARE && field[i] != SPRITE_GOAL && !m.isSquareBox(i))
				{
					m.setSquare(i, 9);
					nb_case_morte++;
					deadLocks_list.push_back(i);
					evo++;
				}
			}
			cote_mur = 0;
			hauteur_mur = 0;
		}

		/**
		* Connection of corners and marking them as deadlocks

		*/

		for (int i = 0; i < deadLocks_list.size(); i++)
		{
			int deadLock = deadLocks_list[i];
			copyDeadLock = deadLock;
			deadLock++;

			/**
			 *Horizontal connecting
			*/
			while (!m.isSquareGoal(deadLock) && !m.isSquareWall(deadLock) && !m.isSquareDeadSquare(deadLock) && !m.isSquareBox(deadLock) && !m.isSquareBoxPlaced(deadLock) && deadLock < field.size() && (m.isSquareWall(m.getCol()) || m.isSquareWall(deadLock - m.getCol())))
			{
				deadLock++;
				if (deadLock >= m.getSize()) {
					deadLock--;
					break;
				}
			}

			if (m.isSquareDeadSquare(deadLock))
			{
				for (int c = copyDeadLock; c < deadLock; c++)
				{
					m.setSquare(c, 9);

				}
			}

			/**
			 *Vertical connecting
			*/
			deadLock = copyDeadLock;
			deadLock = deadLock + m.getCol();


			while (deadLock < m.getSize() && !m.isSquareGoal(deadLock) && !m.isSquareWall(deadLock) && !m.isSquareDeadSquare(deadLock) && !m.isSquareBox(deadLock) && !m.isSquareBoxPlaced(deadLock) && deadLock < field.size() && ((deadLock + 1 < m.getSize() && m.isSquareWall(deadLock + 1)) || m.isSquareWall(deadLock - 1)))
			{
				deadLock = deadLock + m.getCol();
				if (deadLock >= m.getSize()) {
					deadLock -= m.getCol();
					break;
				}


			}

			if (deadLock < m.getSize() && m.isSquareDeadSquare(deadLock))
			{
				for (int c = copyDeadLock; c < deadLock; c = c + m.getCol())
				{
					m.setSquare(c, 9);
				}
			}
		}


	





}


/** 
* Detect if a move will create a dynamique deadLock
* 
*/

bool case_morte::dyn_dead(Maze m, unsigned short position, unsigned char dir)
{
	unsigned short cote_d = 0, cote_g = 0, cote_h = 0, cote_b = 0, cote_hor = 0, cote_ver = 0;
	unsigned short position_box = 0, position_futur = 0, murd = 0, murh = 0, murg = 0, murb = 0, boxh = 0, boxb = 0, boxg = 0, boxd = 0;
	bool tst;


	if (dir == TOP && m.isSquareBoxNonPlaced(position - m.getCol()) && !m.isSquareGoal(position - 2 * m.getCol()))
	{

		position_box = position - m.getCol();
		position_futur = position_box - m.getCol();




		if (!m.isSquareWalkable(position_futur - m.getCol()))
		{
			cote_h++;
		}


		if (!m.isSquareWalkable(position_futur - 1))
		{
			if (m.isSquareBoxNonPlaced(position_futur - 1))
			{

				boxg++;
			}
			if (m.isSquareWall(position_futur - 1))
			{
				murg++;
			}
			cote_g++;
			cote_ver++;
		}
		if (!m.isSquareWalkable(position_futur + 1))
		{
			if (m.isSquareBoxNonPlaced(position_futur + 1))
			{

				boxd++;
			}
			if (m.isSquareWall(position_futur + 1))
			{
				murd++;
			}
			cote_d++;
			cote_ver++;
		}
	}
	if (dir == BOTTOM && m.isSquareBoxNonPlaced(position + m.getCol()) && !m.isSquareGoal(position + 2 * m.getCol()))
	{
		position_box = position + m.getCol();
		position_futur = position_box + m.getCol();
		if (!m.isSquareWalkable(position_futur + m.getCol()))
		{
			if (m.isSquareBoxNonPlaced(position_futur + m.getCol()))
				boxh++;
			if (m.isSquareWall(position_futur + m.getCol()))
			{
				murb++;
			}
			cote_b++;
			cote_hor++;
		}

		if (!m.isSquareWalkable(position_futur - 1))
		{
			cote_g++;
			cote_ver++;
			if (m.isSquareBoxNonPlaced(position_futur - 1))
				boxg++;
			if (m.isSquareWall(position_futur - 1))
			{
				murg++;
			}
		}
		if (!m.isSquareWalkable(position_futur + 1))
		{
			if (m.isSquareBoxNonPlaced(position_futur + 1))
			{

				boxd++;
			}
			if (m.isSquareWall(position_futur + 1))
			{
				murd++;
			}
			cote_d++;
			cote_ver++;
		}
	}

	if (dir == LEFT && m.isSquareBoxNonPlaced(position - 1) && !m.isSquareGoal(position - 2))
	{
		position_box = position - 1;
		position_futur = position_box - 1;
		if (!m.isSquareWalkable(position_futur - m.getCol()))
		{
			if (m.isSquareBoxNonPlaced(position_futur - m.getCol()))
				boxh++;
			if (m.isSquareWall(position_futur - m.getCol()))
			{
				murh++;
			}
			cote_h++;
			cote_hor++;
		}

		if (!m.isSquareWalkable(position_futur - 1))
		{
			cote_g++;
			cote_ver++;
			if (m.isSquareBoxNonPlaced(position_futur - 1))
				boxg++;
			if (m.isSquareWall(position_futur - 1))
			{
				murg++;
			}
		}
		if (!m.isSquareWalkable(position_futur + m.getCol()))
		{
			if (m.isSquareBoxNonPlaced(position_futur + m.getCol()))
				boxh++;
			if (m.isSquareWall(position_futur + m.getCol()))
			{
				murb++;
			}
			cote_b++;
			cote_hor++;
		}
	}

	if (dir == RIGHT && m.isSquareBoxNonPlaced(position + 1) && !m.isSquareGoal(position + 2))
	{
		position_box = position + 1;
		position_futur = position_box + 1;
		if (!m.isSquareWalkable(position_futur - m.getCol()))
		{
			if (m.isSquareBoxNonPlaced(position_futur - m.getCol()))
				boxh++;

			if (m.isSquareWall(position_futur - m.getCol()))
			{
				murh++;
			}
			cote_h++;
			cote_hor++;
		}

		if (!m.isSquareWalkable(position_futur + m.getCol()))
		{
			if (m.isSquareBoxNonPlaced(position_futur + m.getCol()))
				boxb++;
			if (m.isSquareWall(position_futur + m.getCol()))
			{
				murb++;
			}
			cote_b++;
			cote_hor++;
		}

		if (!m.isSquareWalkable(position_futur + 1))
		{
			if (m.isSquareBoxNonPlaced(position_futur + 1))
			{

				boxd++;
			}
			if (m.isSquareWall(position_futur + 1))
			{
				murd++;
			}
			cote_d++;
			cote_ver++;
		}
	}



	if (cote_hor >= 1 && cote_ver >= 1)
	{

		if (cote_h > 0 && cote_d > 0 && (!m.isSquareWalkable(position_futur + 1 - m.getCol())))
			return true;

		if (cote_h&&cote_g && (!m.isSquareWalkable(position_futur - 1 - m.getCol())))
			return true;

		if (cote_b&&cote_g && (!m.isSquareWalkable(position_futur - 1 + m.getCol()))) {
			return true;
		}

		if (cote_b&&cote_d && (!m.isSquareWalkable(position_futur + 1 + m.getCol())))
			return true;

		if (boxb > 0 && murd > 0 && m.isSquareWall(position_futur - 1 + m.getCol()))
			return true;
		if (boxb > 0 && murg > 0 && m.isSquareWall(position_futur + 1 + m.getCol()))
			return true;
		if (boxh > 0 && murg > 0 && m.isSquareWall(position_futur + 1 - m.getCol()))
			return true;
		if (boxh > 0 && murd > 0 && m.isSquareWall(position_futur - 1 - m.getCol()))
			return true;
		if (boxg > 0 && murb > 0 && m.isSquareWall(position_futur - 1 - m.getCol())) {

		}
		if (boxg > 0 && murh > 0 && m.isSquareWall(position_futur - 1 + m.getCol()))
			return true;
		if (boxd > 0 && murh > 0 && m.isSquareWall(position_futur + 1 + m.getCol()))
			return true;
		if (boxd > 0 && murb > 0 && m.isSquareWall(position_futur + 1 - m.getCol()))
			return true;


		if (murg > 0 && m.isSquareWall(position_futur - 2 * m.getCol()) && m.isSquareWall(position_futur - m.getCol() - 1) && m.isSquareBoxNonPlaced(position_futur - m.getCol() + 1) && m.isSquareWall(position_futur - m.getCol() * 2 + 1))
			return true;
		if (murh > 0 && m.isSquareWall(position_futur - 2) && m.isSquareWall(position_futur - m.getCol() - 1) && m.isSquareBoxNonPlaced(position_futur + m.getCol() - 1) && m.isSquareWall(position_futur + m.getCol() - 2))
			return true;
		if (murh > 0 && m.isSquareWall(position_futur + 2) && m.isSquareWall(position_futur - m.getCol() + 1) && m.isSquareBoxNonPlaced(position_futur + m.getCol() + 1) && m.isSquareWall(position_futur + 2 + m.getCol()))
			return true;
		if (murd > 0 && m.isSquareWall(position_futur - 2 * m.getCol()) && m.isSquareWall(position_futur - m.getCol() + 1) && m.isSquareBoxNonPlaced(position_futur - m.getCol() - 1) && m.isSquareWall(position_futur - 1 - 2 * m.getCol()))
			return true;
		if (murg > 0 && m.isSquareWall(position_futur + 2 * m.getCol()) && m.isSquareWall(position_futur + m.getCol() - 1) && m.isSquareBoxNonPlaced(position_futur + m.getCol() + 1) && m.isSquareWall(position_futur + 2 * m.getCol() + 1))
			return true;
		if (murb > 0 && m.isSquareWall(position_futur - 2) && m.isSquareWall(position_futur + m.getCol() - 1) && m.isSquareBoxNonPlaced(position_futur - m.getCol() - 1) && m.isSquareWall(position_futur - 2 - m.getCol()))
			return true;
		if (murb > 0 && m.isSquareWall(position_futur + 2) && m.isSquareWall(position_futur - m.getCol() + 1) && m.isSquareBoxNonPlaced(position_futur - m.getCol() + 1) && m.isSquareWall(position_futur - 2 - m.getCol()))
			return true;
		if (murd > 0 && m.isSquareWall(position_futur + 2 * m.getCol()) && m.isSquareWall(position_futur + m.getCol() + 1) && m.isSquareBoxNonPlaced(position_futur + m.getCol() - 1) && m.isSquareWall(position_futur - 1 + 2 * m.getCol()))
			return true;

	}

	return false;
}
