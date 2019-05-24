#ifndef UTIL_H
#define UTIL_H
#include <queue>
#include "src/Maze/Maze.h"
#include <vector>
#include <string>
#include "src/utils/Coord.h"
#include "src/utils/Util.h"
#include <iostream>
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include <algorithm>
#include <sstream>	
#include <iostream>
#include <unordered_set>
class Util
{
public:
	Util();

	~Util();
public:
	//Is the trackBFS Type of the BFS in relier_point(...)
	class BFSCase_relier_point :public  NodeCaseMother {
	public:
		BFSCase_relier_point(std::vector<unsigned char> field, unsigned short pos, int id, int pId, char dir)
			: NodeCaseMother(id, pId), field(field), position(pos), mov(dir) {};
		~BFSCase_relier_point() {};

		std::vector<unsigned char> field;		unsigned short position;

		char mov;
	};
public:
	void vider(std::queue<unsigned short> &t);
	void vider(std::queue<std::vector<unsigned char>> &t);
	void vider(std::queue< BFSCase_relier_point> &queue);


	std::vector<bool> calcZoneAccessible(const Maze* m, short &normPos);
	std::vector<unsigned short> relier_point(Maze m, std::vector <unsigned short>);
	std::string choose_level();
	/**
	* Return the path beetween the squareID send in parameters and the nearest goal.
	* If no possible path, return null
	* path is the id of all the square
	BM: box movement (path is like a path if we push a box)
	*
	*/
	std::deque<short> getPathSquareToGoalBM(const Maze* m, short squareID);

	/**
	* Return the path beetween the squareID send in parameters and the toSquare goal.
	* If no possible path, return null
	* path is the id of all the square
	* BM: box movement (path is like a path if we push a box)
	*/
	std::deque<short> getPathSquareToSquareBM(const Maze* m, short fromSquare, short toSquare);
	std::vector< Node::NodeRetrackInfo> getPathSquareToSquareZoneMethod(const Maze* m, short fromSquare, short toSquare, short posPlayer);
	std::deque<short> getPathSquareToSquarePM(const Maze* m, short fromSquare, short toSquare);

	std::vector<short>  getDistMapOfSquare(const Maze *m, short toSquare);


	/**
	* display a vector of the size of the field
	*/
	void dispVector(const Maze* m, std::vector<short> vec);
	void dispVector(const Maze* m, std::vector<bool> vec);



private:
	std::vector<BFSCase_relier_point> marque;
	bool compare(BFSCase_relier_point tstCase);
	bool marqued(short acc, const  Maze *m, std::unordered_set<std::string > &marqueZoneBFS);


};



#endif // UTIL_H
