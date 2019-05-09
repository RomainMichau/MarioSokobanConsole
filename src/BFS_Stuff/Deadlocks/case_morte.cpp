#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include <fstream>
#include <iomanip>
#include "src/BFS_Stuff/DeadLocks/Case_morte.h"
#include <unordered_set>
#include "src/utils/Util.h"

Case_morte::Case_morte(Maze *m)
    :nb_case_morte(0),m(m)
{
    //ctor
}

Case_morte::~Case_morte()
{
    //dtor
}



/**
* will detect all deadlocks with a BFS system (if a square can not reach a goal with BFS, it is not a deadlocks)
* algo act like if there is no box on the field
*/
void Case_morte::detect_dead_with_BFS_idealGoal(Maze& maze,short idealGoal)
{
	Util u;
	for (unsigned int square = 0; square < maze.getSize(); square++)
	{
		if (!maze.isSquareWall(square)  && u.getPathSquareToSquarePBM(&maze, square, idealGoal).empty())
		{
			maze.setSquare(square, SPRITE_DEADSQUARE);
		}
	}
}

/**
* will detect all deadlocks with a BFS system (if a square can not reach a goal with BFS, it is not a deadlocks)
* algo act like if there is no box on the field
*/
void Case_morte::detect_dead_with_BFS()
{
    Util u;
    for (unsigned int square = 0; square < m->getSize(); square++)
    {
        if (!m->isSquareWall(square)&&!m->isSquareGoal(square)&&  u.getPathSquareToGoalPBM(m, square).empty())
        {
            m->setSquare(square, SPRITE_DEADSQUARE);
        }
    }
}

/**
* Detect if a move will create a dynamique deadLock
*
*/
bool Case_morte::detect_dyn_dead( unsigned short position, unsigned char dir)
{
    unsigned short cote_d = 0, cote_g = 0, cote_h = 0, cote_b = 0, cote_hor = 0, cote_ver = 0;
    unsigned short position_box = 0, position_futur = 0, murd = 0, murh = 0, murg = 0, murb = 0, boxh = 0, boxb = 0, boxg = 0, boxd = 0;

    if (dir == TOP && m->isSquareBoxNonPlaced(position - m->getCol()) && !m->isSquareGoal(position - 2 * m->getCol()))
    {

        position_box = position - m->getCol();
        position_futur = position_box - m->getCol();



        if (!m->isSquareWalkable(position_futur - m->getCol()))
        {
            cote_h++;
        }


        if (!m->isSquareWalkable(position_futur - 1))
        {
            if (m->isSquareBoxNonPlaced(position_futur - 1))
            {

                boxg++;
            }
            if (m->isSquareWall(position_futur - 1))
            {
                murg++;
            }
            cote_g++;
            cote_ver++;
        }
        if (!m->isSquareWalkable(position_futur + 1))
        {
            if (m->isSquareBoxNonPlaced(position_futur + 1))
            {

                boxd++;
            }
            if (m->isSquareWall(position_futur + 1))
            {
                murd++;
            }
            cote_d++;
            cote_ver++;
        }
    }
    if (dir == BOTTOM && m->isSquareBoxNonPlaced(position + m->getCol()) && !m->isSquareGoal(position + 2 * m->getCol()))
    {
        position_box = position + m->getCol();
        position_futur = position_box + m->getCol();
        if (!m->isSquareWalkable(position_futur + m->getCol()))
        {
            if (m->isSquareBoxNonPlaced(position_futur + m->getCol()))
                boxh++;
            if (m->isSquareWall(position_futur + m->getCol()))
            {
                murb++;
            }
            cote_b++;
            cote_hor++;
        }

        if (!m->isSquareWalkable(position_futur - 1))
        {
            cote_g++;
            cote_ver++;
            if (m->isSquareBoxNonPlaced(position_futur - 1))
                boxg++;
            if (m->isSquareWall(position_futur - 1))
            {
                murg++;
            }
        }
        if (!m->isSquareWalkable(position_futur + 1))
        {
            if (m->isSquareBoxNonPlaced(position_futur + 1))
            {

                boxd++;
            }
            if (m->isSquareWall(position_futur + 1))
            {
                murd++;
            }
            cote_d++;
            cote_ver++;
        }
    }

    if (dir == LEFT && m->isSquareBoxNonPlaced(position - 1) && !m->isSquareGoal(position - 2))
    {
        position_box = position - 1;
        position_futur = position_box - 1;
        if (!m->isSquareWalkable(position_futur - m->getCol()))
        {
            if (m->isSquareBoxNonPlaced(position_futur - m->getCol()))
                boxh++;
            if (m->isSquareWall(position_futur - m->getCol()))
            {
                murh++;
            }
            cote_h++;
            cote_hor++;
        }

        if (!m->isSquareWalkable(position_futur - 1))
        {
            cote_g++;
            cote_ver++;
            if (m->isSquareBoxNonPlaced(position_futur - 1))
                boxg++;
            if (m->isSquareWall(position_futur - 1))
            {
                murg++;
            }
        }
        if (!m->isSquareWalkable(position_futur + m->getCol()))
        {
            if (m->isSquareBoxNonPlaced(position_futur + m->getCol()))
                boxh++;
            if (m->isSquareWall(position_futur + m->getCol()))
            {
                murb++;
            }
            cote_b++;
            cote_hor++;
        }
    }

    if (dir == RIGHT && m->isSquareBoxNonPlaced(position + 1) && !m->isSquareGoal(position + 2))
    {
        position_box = position + 1;
        position_futur = position_box + 1;
        if (!m->isSquareWalkable(position_futur - m->getCol()))
        {
            if (m->isSquareBoxNonPlaced(position_futur - m->getCol()))
                boxh++;

            if (m->isSquareWall(position_futur - m->getCol()))
            {
                murh++;
            }
            cote_h++;
            cote_hor++;
        }

        if (!m->isSquareWalkable(position_futur + m->getCol()))
        {
            if (m->isSquareBoxNonPlaced(position_futur + m->getCol()))
                boxb++;
            if (m->isSquareWall(position_futur + m->getCol()))
            {
                murb++;
            }
            cote_b++;
            cote_hor++;
        }

        if (!m->isSquareWalkable(position_futur + 1))
        {
            if (m->isSquareBoxNonPlaced(position_futur + 1))
            {

                boxd++;
            }
            if (m->isSquareWall(position_futur + 1))
            {
                murd++;
            }
            cote_d++;
            cote_ver++;
        }
    }



    if (cote_hor >= 1 && cote_ver >= 1)
    {

        if (cote_h > 0 && cote_d > 0 && (!m->isSquareWalkable(position_futur + 1 - m->getCol())))
            return true;

        if (cote_h&&cote_g && (!m->isSquareWalkable(position_futur - 1 - m->getCol())))
            return true;

        if (cote_b&&cote_g && (!m->isSquareWalkable(position_futur - 1 + m->getCol())))
        {
            return true;
        }

        if (cote_b&&cote_d && (!m->isSquareWalkable(position_futur + 1 + m->getCol())))
            return true;

        if (boxb > 0 && murd > 0 && m->isSquareWall(position_futur - 1 + m->getCol()))
            return true;
        if (boxb > 0 && murg > 0 && m->isSquareWall(position_futur + 1 + m->getCol()))
            return true;
        if (boxh > 0 && murg > 0 && m->isSquareWall(position_futur + 1 - m->getCol()))
            return true;
        if (boxh > 0 && murd > 0 && m->isSquareWall(position_futur - 1 - m->getCol()))
            return true;
        if (boxg > 0 && murb > 0 && m->isSquareWall(position_futur - 1 - m->getCol()))
        {

        }
        if (boxg > 0 && murh > 0 && m->isSquareWall(position_futur - 1 + m->getCol()))
            return true;
        if (boxd > 0 && murh > 0 && m->isSquareWall(position_futur + 1 + m->getCol()))
            return true;
        if (boxd > 0 && murb > 0 && m->isSquareWall(position_futur + 1 - m->getCol()))
            return true;


        if (murg > 0 && m->isSquareWall(position_futur - 2 * m->getCol()) && m->isSquareWall(position_futur - m->getCol() - 1) && m->isSquareBoxNonPlaced(position_futur - m->getCol() + 1) && m->isSquareWall(position_futur - m->getCol() * 2 + 1))
            return true;
        if (murh > 0 && m->isSquareWall(position_futur - 2) && m->isSquareWall(position_futur - m->getCol() - 1) && m->isSquareBoxNonPlaced(position_futur + m->getCol() - 1) && m->isSquareWall(position_futur + m->getCol() - 2))
            return true;
        if (murh > 0 && m->isSquareWall(position_futur + 2) && m->isSquareWall(position_futur - m->getCol() + 1) && m->isSquareBoxNonPlaced(position_futur + m->getCol() + 1) && m->isSquareWall(position_futur + 2 + m->getCol()))
            return true;
        if (murd > 0 && m->isSquareWall(position_futur - 2 * m->getCol()) && m->isSquareWall(position_futur - m->getCol() + 1) && m->isSquareBoxNonPlaced(position_futur - m->getCol() - 1) && m->isSquareWall(position_futur - 1 - 2 * m->getCol()))
            return true;
        if (murg > 0 && m->isSquareWall(position_futur + 2 * m->getCol()) && m->isSquareWall(position_futur + m->getCol() - 1) && m->isSquareBoxNonPlaced(position_futur + m->getCol() + 1) && m->isSquareWall(position_futur + 2 * m->getCol() + 1))
            return true;
        if (murb > 0 && m->isSquareWall(position_futur - 2) && m->isSquareWall(position_futur + m->getCol() - 1) && m->isSquareBoxNonPlaced(position_futur - m->getCol() - 1) && m->isSquareWall(position_futur - 2 - m->getCol()))
            return true;
        if (murb > 0 && m->isSquareWall(position_futur + 2) && m->isSquareWall(position_futur - m->getCol() + 1) && m->isSquareBoxNonPlaced(position_futur - m->getCol() + 1) && m->isSquareWall(position_futur - 2 - m->getCol()))
            return true;
        if (murd > 0 && m->isSquareWall(position_futur + 2 * m->getCol()) && m->isSquareWall(position_futur + m->getCol() + 1) && m->isSquareBoxNonPlaced(position_futur + m->getCol() - 1) && m->isSquareWall(position_futur - 1 + 2 * m->getCol()))
            return true;

    }

    return false;
}
