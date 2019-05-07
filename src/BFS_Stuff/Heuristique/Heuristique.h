#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/MapStat.h"
#include "src/BFS_Stuff/BFS_Objects/BFSCase.h"
#include "src/BFS_Stuff/DeadLocks/Case_morte.h"
class Heuristique
{
public:
    Heuristique(Maze *m, int coefA, int coefB);
    ~Heuristique();
    void calcHeuristiqueNote( BFSCase *bfsCase, short boxPushedID, short newPos);
	void generateMapStateFromField(BFSCase *bfsPlusCase);
	   
private:
   

	void calcMapStat();

	void refreshMapStat();

	BFSCase *bfsCase;

    /**
    * Stat calculators
    */
    std::vector<short> calcFrequentationSquares();

	std::vector<short> calcMapDistanceFromNearestGoals();

	std::vector<short> calcMapDistanceFromIdealGoal();


    /**
    * return the pivot point of mapStat
    * definit of pivotPoint: the point with the most frequentation.
    * if there is many point with the same max frequentation, then the farest from the goal win
    * @see MapStat
    */
    short calcPivotPointPos();

	/**
	* return the goal wich is the farest from the pivot point
	*/
	short calcIdealGoalPos();


    /**
    * Note calculator
    */
	unsigned short calc_note_distance_box_bfs_multiple_box();
	unsigned short calc_note_distance_with_distMap();


	Util u;
	Maze *m;
	Note note;
	Case_morte deadlocks;


};

#endif // HEURISTIQUE_H
