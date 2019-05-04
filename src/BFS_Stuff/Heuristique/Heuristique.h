#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H
#include "src/Maze/maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/MapStat.h"
class Heuristique
{
public:
    Heuristique(Maze *m);
    ~Heuristique();
    Note heuristiquemaline( int noteA, int noteB, int caisse);
    



private:
    /**
    * Attribut
    */
    MapStat mapStat;

    /**
    * Stat calculators
    */
    std::vector<short> calcFrequentationSquares();

	std::vector<short> calcMapDistanceFromNearestGoals();

    /**
    * return the pivot point of mapStat
    * definit of pivotPoint: the point with the most frequentation.
    * if there is many point with the same max frequentation, then the farest from the goal win
    * @see MapStat
    */
    short getPivotPoint();

	/**
	* return the goal wich is the farest from the pivot point
	*/
	short getIdealGoal();


    /**
    * Note calculator
    */
    unsigned short calc_note_distance_box_bfs_multiple_box();
    unsigned short calc_note_disance_perso();
    unsigned short calc_note_goal_access();
    unsigned short calc_note_distance_box_bfs_one_box( int numBox);

	Maze *m;



};

#endif // HEURISTIQUE_H
