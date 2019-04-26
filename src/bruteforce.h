#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include "maze.h"


class Bruteforce
{
    public:
        Bruteforce();
       ~Bruteforce();
        int m_cpt;
        std::vector<unsigned char> forcage(Maze m);


    private:

    std::vector<unsigned short> resolution;
    std::vector<unsigned char> chemin;





};

#endif // BRUTEFORCE_H
