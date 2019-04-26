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
		
        void detect_dead(Maze &m);
        bool dyn_dead(Maze m, unsigned short position, unsigned char dir);

    protected:

    private:
        std::vector<unsigned short> liste;
int nb_case_morte;


};

#endif // CASE_MORTE_H
