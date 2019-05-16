#ifndef HEURISTIQUEC_H
#define HEURISTIQUEC_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
class HeuristiqueClassique:public AHeuristique
{
public:




	/**
	* Represent the calculated stat and informations about the Game	*
	* only the information which are true for ALL the game are in this class
	*/

public:
	HeuristiqueClassique(Maze *m, int coefA, int coefB); 
	~HeuristiqueClassique();
	void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos);
	virtual std::string sayHello() { return "Classique Heuristique"; };
	Chapter* getChapters() { return NULL; };
private:


};


#endif // HEURISTIQUE_H
