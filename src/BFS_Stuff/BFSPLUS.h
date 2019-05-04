#ifndef BFSPLUS_H
#define BFSPLUS_H
#include "src/Maze/maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include <unordered_set>
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





public:
    class BFSPLUSCase
    {
    public:
        BFSPLUSCase(std::vector<bool> accessibleZone, std::vector<unsigned char> field, Note note, unsigned short profondeur, int classement) :
            accessibleZone(accessibleZone), field(field), note(note), profondeur(profondeur), classement(classement)
        {

        }
        std::vector<bool> accessibleZone;
        std::vector<unsigned char> field;
        Note note;
        unsigned short profondeur;
        int classement;
    };

    struct BestBFSCase
    {
        bool operator()(BFSPLUSCase b1, BFSPLUSCase b2) const
        {
            return b1.note.get_note_total() < b2.note.get_note_total();
        }
    };



};

#endif // BFSPLUS_H
