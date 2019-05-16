#ifndef AHEURISTIQUE_H
#define AHEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
class AHeuristique
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
	AHeuristique(Maze *m, int coefA, int coefB);
	virtual ~AHeuristique();
	virtual void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos)=0;
	virtual std::string sayHello()=0; 
	virtual Chapter* getChapters() = 0;
	
protected:

	Util u;
	Maze *m;
	Note note;
	Case_morte deadlocks;

	/**
	* Note calculator
	*/
	unsigned short calc_note_distance_box_bfs_multiple_box();



};


#endif // HEURISTIQUE_H
