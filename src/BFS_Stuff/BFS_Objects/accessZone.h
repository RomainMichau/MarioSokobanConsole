#ifndef ACCESS_ZONE_H
#define ACCESS_ZONE_H
/**
 * \file AccessZone.h
 * \brief declaration of the class AccessZone
 * \author Romain Michau
 * \version 2.1
 */
#include "src/Maze/MazeMap.h"

#include <vector>
#include <unordered_set>

/** \class AccessZone
* \brief Represent the zone accessible by the player and his normalize position in a Node
*/
class AccessZone
{

private:
	 MazeMap<char> accessibleZone;
     short nPos;


public:
    AccessZone(const  MazeMap<char>   accessibleZone, const short nPos) :accessibleZone(accessibleZone), nPos(nPos) {};
    ~AccessZone() {};

	MazeMap<char> getAccessibleZone() const
    {
        return accessibleZone;
    };
    bool isAccessible(const short pos)
    {
		return accessibleZone[pos];
    };
    short getNPos()const
    {
        return nPos;
    };
};
#endif
