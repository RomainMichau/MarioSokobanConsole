#ifndef MAPSTAT_H
#define MAPSTAT_H

#include <vector>
/**
* Represent the calculated stat and informations about the maze
*/
class MapStat
{
public:
    MapStat();
    ~MapStat();

    /**
    * GET/SET
    */
    std::vector<short> getMapFrequentationSquares()
    {
        return mapFrequentationSquares;
    }
    void setMapFrequentationSquares(std::vector<short> map)
    {
        this->mapFrequentationSquares = map;
    }

    std::vector<short> getMapDistanceFromGoal()
    {
        return this->mapDistanceFromGoal;
    }
    void setMapDistanceFromGoal(std::vector<short> map)
    {
        this->mapDistanceFromGoal = map;
    }


private:
    /**
    * a vector of the side of the field whcih represent the distance beetween each square and the goal
    */
    std::vector<short> mapDistanceFromGoal;
    /*
    * a vector of the side of the field wich is calculate like that:
    *	we make a bfs for fin the way beetween each box and the goal
    *	for each square we count how many time a box passed on it
    *	we put this info in this vector
    */
    std::vector<short> mapFrequentationSquares;

    /**
    * the pivotPoint is a square of the field where the passage is necessary for reach any goals
    */
    short pivotPoint;

    /**
    * this is the goal which is the farest for the pivotPoint
    */
    short idealGoal;
};

#endif // MAPSTAT_H
