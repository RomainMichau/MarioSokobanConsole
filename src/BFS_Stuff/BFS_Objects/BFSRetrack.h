#ifndef BFSRETRACK_H
#define BFSRETRACK_H
#include "src/BFS_Stuff/BFS_Objects/MapStat.h"
class BFSRetrack {
public:
	
	BFSRetrack(int id, int idParent,short pos)
		:id(id), idParent(idParent),pos(pos)
	{

	}

	int id;
	int idParent;
	short pos;
};

#endif //BFSRETRACK_H