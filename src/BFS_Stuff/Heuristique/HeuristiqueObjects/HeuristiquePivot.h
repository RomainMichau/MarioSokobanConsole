#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
#include <unordered_map>
/**
*	Class of heuristique wich use a Pivot Point Method (see def below)
*	Method: When the pivot point is reached by a box, a macro drive the box to the ideal goal
*/
class HeuristiquePivot :public AHeuristique
{
	friend class FHeuristique;

public:


	/**
	* Represent the calculated stat and informations about the Game	*
	* only the information which are true for ALL the game are in this class
	*/
	class GameStat {
	public:
		GameStat(std::vector<short> mapFrequentationSquares, short pivotPoint) :
			mapFrequentationSquares(mapFrequentationSquares), pivotPoint(pivotPoint) {};
		short getPivotPointPos() const { return pivotPoint; };
		void setPivotPoint(short pivotPoint) { this->pivotPoint = pivotPoint; }
		std::vector<short> getMapFrequentationSquares() const
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
	/**
	* PUBLIC METHOD
	*/
	~HeuristiquePivot();
	void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos);
	virtual std::string sayHello() { return "Pivot Method Heuristique"; };
	Chapter* getChapters() { return &chapters; };
	std::pair<short, short> macroMove(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxID);
private:

	int nb_caisse_place_best;
	/**
	* PRIVATE METHOD
	*/
	HeuristiquePivot(Maze *m, int coefA, int coefB, GameStat gameStat);
	Chapter  calcChapter();
	void calcMacroPath();

	/**
	* PRIVATE ATTRIBUT
	*/




	/**
	* stats about the game
	*/
	const GameStat gameStat;
	/*
	* lionked list of chapterts order by number:
	*	chapters[0]=> chapter0
	*	chapters[1]=> chapter1
	*	chapters[2]=> chapter2
	*/
	Chapter  chapters;
};


#endif // HEURISTIQUE_H
