#ifndef BFS_H
#define BFS_H
#include "maze.h"
#include "queue"
#include "stock_field.h"

class BFS
{
    public:
        BFS();
       ~BFS();
        std::vector<unsigned char> letsgobfs(Maze m);
        void reinit();


    private:
        std::vector<unsigned short> resolution;
        std::vector<unsigned char> chemin;
        std::vector<std::vector<bool>> marque_position;
        std::queue <std::vector<bool>> file_position;
        std::queue <std::vector<unsigned char>> file_field;
      //  std::vector<std::vector<unsigned char>> marque_field;
      stock_field marque_field;
        std::vector<unsigned short>origin;  //je fais un tableau ou j'alterne la postion precedente et le mouvement
                                            // necessaire pour arriver a cette nouvelle etat
        bool compare(std::vector<unsigned char> vec);
        void invert(std::vector<unsigned short> &vec);

};

#endif // BFS_H
