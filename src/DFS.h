#ifndef DFS_H
#define DFS_H
#include <stack>
#include "../src/BFS.h"
#include <queue>
#include "maze.h"
#include <vector>
#include <string>
#include "../utils/coord.h"
#include <iostream>

class DFS
{
    public:
        DFS();
        ~DFS();
        std::vector<unsigned char> letsgodfs(Maze m);
        void reinit();

    protected:


    private:
    std::vector<unsigned short> resolution;
    void invert(std::vector<unsigned short> &vec);
    std::vector<unsigned char> chemin;
     std::stack <std::vector<bool>> pile_position;
    std::stack<unsigned short> pile_classement;
    std::stack<std::vector<unsigned char>> pile_field;
    std::vector<std::vector<bool>> marque_position;
    std::vector<std::vector<unsigned char>>marque_field;
    std::vector<unsigned short> origin;
    bool compare(std::vector<unsigned char> vec,std::vector<bool> a);

};

#endif // DFS_H
