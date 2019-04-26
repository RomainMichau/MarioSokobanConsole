#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H
#include "maze.h"
#include "note.h"
class heuristique
{
    public:
        heuristique();
        ~heuristique();
        Note heuristiquemaline(Maze m,int noteA,int noteB,int caisse);
        unsigned short heuristiquenaif(Maze m);

    protected:

        unsigned short note_distance_box_bfs_multiple_box(Maze m);
        unsigned short note_disance_perso(Maze m);
        unsigned short note_goal_access(Maze m);
        unsigned short note_distance_box_manhatan(Maze m);
        unsigned short note_distance_box_bfs_one_box(Maze m,int numBox);

    private:
};

#endif // DJIKSTRA_H
