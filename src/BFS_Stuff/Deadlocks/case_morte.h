/**
 * \file case_morte.h
 * \brief declaration of the class case_morte
 * \author romain michau
 * \version 2.1
 */

#ifndef CASE_MORTE_H
#define CASE_MORTE_H
#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include "src/utils/util.h"
#include <fstream>
#include <iomanip>
#include <unordered_set>
#include "src/BFS_Stuff/DeadLocks/case_morte.h" 
#include "src/BFS_Stuff/BFS_Objects/Node.h"
class Case_morte
{

	struct VectorHash {
		size_t operator()(const std::unordered_set<unsigned short>& v) const {
			std::hash<unsigned short> hasher;
			size_t seed = 0;
			for (int i : v) {
				seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
			return seed;
		}
	};

public:
	Case_morte(Maze *m);
	~Case_morte();

	void detect_dead_with_BFS_idealGoal(Maze& m, short idealGoal);
	void detect_dead_with_BFS();
	bool detect_dyn_dead_3( Node *node);
	bool isMarqueAsDeadlocks(Node *node);
	/**
	* will execute a bfs on each square to see if an exit is accesible
	* if not the square will be mark as dead_sqare
	* will ofc not toak in accoount any box
	*/

protected:

private:
	bool isADynDeadlock(std::unordered_set<unsigned short> aglomerateBoxes);
	std::vector<unsigned short> deadLocks_list;
	int nb_case_morte;
	Maze *m;
	Util u;
	// liste des cas de deadLocks connu
	std::unordered_set<std::unordered_set<unsigned short>, VectorHash> knownDealocks;
};

#endif // CASE_MORTE_H
