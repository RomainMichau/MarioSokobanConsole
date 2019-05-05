#ifndef MAPSTAT_H
#define MAPSTAT_H

#include <vector>
/**
* Represent the calculated stat and informations about the maze
*/
class MapStat
{
public:
	MapStat(int numberOfGoal);
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

	short getPivotPointPos() { return pivotPoint; };
	void setPivotPoint(short pivotPoint) { this->pivotPoint = pivotPoint; }

	short getcIdealGoalPos() { return idealGoal; }
	void setIdealGoal(short idealGoal) { this->idealGoal = idealGoal; }

	bool isBoxPlaceOnIdealGoal(int i) { return boxIsPlaceOnIdealGoal[i]; }
	void setBoxIsPlaceOnIdealGoal(int i,bool boxPlaced) { boxIsPlaceOnIdealGoal[i] = boxPlaced; }



private:
	/**
	* a vector of the side of the field whcih represent the distance beetween each square and the Idealgoal
	* wil change whenever the ideal goal change
	*/
	std::vector<short> mapDistanceFromGoal;
	/*
	* a vector of the side of the field wich is calculate like that:
	*	we make a bfs for fin the way beetween each box and the goal
	*	for each square we count how many time a box passed on it
	*	we put this info in this vector
	*
	* will not change during the game
	*/
	std::vector<short> mapFrequentationSquares;

	/**
	* the pivotPoint is a square of the field where the passage is necessary for reach any goals
	* will never change during the game
	*/
	short pivotPoint;

	/**
	* this is the goal which is the farest for the pivotPoint and which dont have a box on it
	* will change whenever a box is set a the current ideal goal
	*/
	short idealGoal;

	/**
	* true if box[id] is on its idealGoal
	*/
	std::vector<bool> boxIsPlaceOnIdealGoal;
};

#endif // MAPSTAT_H
