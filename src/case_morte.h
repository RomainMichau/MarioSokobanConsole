#ifndef CASE_MORTE_H
#define CASE_MORTE_H
#include "maze.h"
#include "../utils/console.h"
#include "../utils/coord.h"
#include <fstream>
#include <iomanip>
#include "case_morte.h"

class case_morte
{
    public:
        case_morte();
        ~case_morte();
		
		void detect_dead_staticMethod(Maze &m);
	
		void detect_dead_with_BFS(Maze &m);
        bool dyn_dead(Maze m, unsigned short position, unsigned char dir);
		/**
	* will execute a bfs on each square to see if an exit is accesible
	* if not the square will be mark as dead_sqare
	* will ofc not toak in accoount any box
	*/

    protected:

    private:
        std::vector<unsigned short> deadLocks_list;
int nb_case_morte;


};

#endif // CASE_MORTE_H
