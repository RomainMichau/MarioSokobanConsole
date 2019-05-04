#ifndef UTIL_H
#define UTIL_H
#include <queue>
#include "src/Maze/maze.h"
#include <vector>
#include <string>
#include "src/utils/coord.h"
#include "src/utils/util.h"
#include <iostream>
#include "src/BFS_Stuff/Heuristique/note.h"


class Util
{
public:
    Util();
    ~Util();
    void vider(std::queue<unsigned short> &t);
    void vider(std::queue<std::vector<unsigned char>> &t);

    void invert(std::vector<unsigned short> &vec);
    std::vector<bool> calcZoneAccessible(Maze m);
    std::vector<unsigned short> relier_point(Maze m,std::vector <unsigned short>);
    bool compare(std::vector<unsigned char> vec,unsigned short a);
    std::string choose_level();
    /**
    * Return the path beetween the squareID send in parameters and the nearest goal.
    * If no possible path, return null
    * path is the id of all the square
    */
    std::deque<short> getPathSquareToGoal(Maze m, short squareID);

    /**
    * Return the path beetween the squareID send in parameters and the toSquare goal.
    * If no possible path, return null
    * path is the id of all the square
    */
    std::deque<short> getPathSquareToSquare(Maze m, short fromSquare, short toSquare);




    /**
    * display a vector of the size of the field
    */
    void dispVector(Maze m,std::vector<short> vec);
protected:

private:
    std::vector <unsigned short> marque_position;
    std::vector<std::vector<unsigned char>> marque_field;
};

#endif // UTIL_H
