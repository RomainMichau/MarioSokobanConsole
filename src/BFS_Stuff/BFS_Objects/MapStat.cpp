#include "MapStat.h"

MapStat::~MapStat()
{
}

/*
* will set all box as if not placed on ideal goal
*/
MapStat::MapStat(int numberOfGoal)
{
	boxIsPlaceOnIdealGoal.resize(numberOfGoal, false);
	//idealGoals.resize(numberOfGoal, false);
}

