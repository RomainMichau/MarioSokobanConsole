#ifndef BFSPLUS_H
#define BFSPLUS_H
#include "maze.h"
#include "stock_field.h"
#include "note.h"
class BFSPLUS
{
    public:
        BFSPLUS();
        virtual ~BFSPLUS();
        std::vector<unsigned char> bfs_malin(Maze m,bool,int &,int,int,int);
        void reinit();




    private:
        std::vector<unsigned short> resolution;
        std::vector<unsigned char> chemin;
        std::vector <std::vector<bool>> file_position;
        std::vector <unsigned short> file_profondeur;
        std::vector <Note> file_note;
        std::vector <unsigned short> file_classement;
        std::vector <std::vector<unsigned char>> file_field;
        stock_field marque_field;
        std::vector<unsigned short>origin;  //je fais un tableau ou j'alterne la postion precedente et le mouvement
                                            // necessaire pour arriver a cette nouvelle etat
        bool compare(std::vector<unsigned char>,unsigned short);
        void invert(std::vector<unsigned short> &vec);
        bool compare(std::vector<unsigned char> vec);


};

#endif // BFSPLUS_H
