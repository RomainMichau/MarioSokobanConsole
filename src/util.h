#ifndef UTIL_H
#define UTIL_H
#include <queue>
#include "../src/maze.h"
#include <vector>
#include <string>
#include "../utils/coord.h"
#include "util.h"
#include <iostream>
#include "note.h"


class util
{
    public:
        util();
        ~util();
        void vider(std::queue<unsigned short> &t);
        void vider(std::stack<std::vector<unsigned char>> &t);
        void vider(std::stack<unsigned short> &t);
        void vider(std::queue<std::vector<unsigned char>> &t);
        void vider(std::stack<bool> &t);
        void vider(std::queue<std::vector<bool>> &t);
        void invert(std::vector<unsigned short> &vec);
        void vider(std::stack <std::vector<bool>> &t);
        std::vector<unsigned short> doubldim(unsigned short a, Maze m);
        unsigned short rang(std::vector <Note> vec, Note note);     
        std::vector<bool> calcZoneAccessible(Maze m);
        std::vector<unsigned short> relier_point(Maze m,std::vector <unsigned short>);
        bool compare(std::vector<unsigned char> vec,unsigned short a);
        std::string choose_level();
        void dispVector(    std::vector<bool>,Maze);

    protected:

    private:
        std::vector <unsigned short> marque_position;
        std::vector<std::vector<unsigned char>> marque_field;
};

#endif // UTIL_H
