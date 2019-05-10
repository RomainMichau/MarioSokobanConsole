#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/Case_morte.h"
class HeuristiquePivot
{
public:




	/**
	* Represent the calculated stat and informations about the Game	*
	* only the information which are true for ALL the game are in this class
	*/
	class GameStat {
	public:

		short getPivotPointPos() { return pivotPoint; };
		void setPivotPoint(short pivotPoint) { this->pivotPoint = pivotPoint; }
		std::vector<short> getMapFrequentationSquares()
		{
			return mapFrequentationSquares;
		}
		void setMapFrequentationSquares(std::vector<short> map)
		{
			this->mapFrequentationSquares = map;

		}
	private:
		/**
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
	};

public:
	HeuristiquePivot(Maze *m, int coefA, int coefB);
	~HeuristiquePivot();
	void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos);
	Chapter* getChapters() { return &chapters; };
private:

	void calcGameStat();


	Node *node;

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
	short calcPivotPointPos(std::vector<short> distMap);


	Chapter  calcChapter();

	/**
	* Note calculator
	*/
	unsigned short calc_note_distance_box_bfs_multiple_box();
	unsigned short calc_note_distance_box_bfs_multiple_box_new();
	unsigned short calc_note_distance_with_distMap();


	Util u;
	Maze *m;
	Note note;
	Case_morte deadlocks;
	/**
	* stats about the game
	*/
	GameStat gameStat;
	/*
	* lionked list of chapterts order by number:
	*	chapters[0]=> chapter0
	*	chapters[1]=> chapter1
	*	chapters[2]=> chapter2
	*/
	Chapter  chapters;
};


#endif // HEURISTIQUE_H
