#ifndef BFSPLUS_H
#define BFSPLUS_H
#include "src/Maze/maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include <unordered_set>
#include "src/BFS_Stuff/BFS_Objects/BFSCase.h"
class BFSPLUS
{
public:
    BFSPLUS(Maze *m);
    virtual ~BFSPLUS();
    std::vector<unsigned char> bfs_malin( int &noeudvisite, int noteA, int noteB, int plafond);
    void reinit();



private:
    std::vector<unsigned short> resolution;
    std::vector<unsigned char> chemin;
    std::vector< short>origin;  //je fais un tableau ou j'alterne la postion precedente et le mouvement
    // necessaire pour arriver a cette nouvelle etat
    void invert(std::vector<unsigned short> &vec);
	Maze *m;
	   	 


    struct BestBFSCase
    {
        bool operator()(BFSCase b1, BFSCase b2) const
        {
            return b1.note.get_note_total() < b2.note.get_note_total();
        }
    };



};

#endif // BFSPLUS_H
