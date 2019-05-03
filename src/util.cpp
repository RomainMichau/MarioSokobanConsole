#include "util.h"
#include "../src/maze.h"
#include "../utils/console.h"
#include "../utils/coord.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
util::util()
{
    //ctor
}

util::~util()
{
    //dtor
}


void util::vider(std::queue<unsigned short> &t)
{
    while(!t.empty())
        t.pop();

}

void util::vider(std::stack<std::vector<unsigned char>> &t)
{
    while(!t.empty())
        t.pop();

}
void util::vider(std::stack <std::vector<bool>> &t)
{
    while(!t.empty())
        t.pop();

}
void util::vider(std::queue<std::vector<bool>> &t)
{
    while(!t.empty())
        t.pop();

}
void util::vider(std::stack<bool> &t)
{
    while(!t.empty())
        t.pop();

}

void util::vider(std::queue<std::vector<unsigned char>> &t)
{
    while(!t.empty())
        t.pop();

}

void util::vider(std::stack<unsigned short> &t)
{
    while(!t.empty())
        t.pop();

}


std::vector<unsigned short> util::doubldim(unsigned short a, Maze m)
{
    std::vector< unsigned short> vec;
    unsigned short y;
    unsigned short x=a%m.getCol();

    y=(a-x)/m.getCol();
    vec.push_back(x);
    vec.push_back(y);



    return vec;
}

unsigned short util::rang(std::vector <Note> vec, Note note)
{
    unsigned short b=0,c=0;
    volatile int sizee =vec.size();
    while(b<vec.size()&&note.get_note_total()>vec[b].get_note_total())
    {

        b++;
    }
    if(b==vec.size())
        b--;


    return b;
}








/**
* Calculate all the accesble square in the field with BFS
* (endless bfs which end the the queue is empty)
*/
std::vector<bool> util::calcZoneAccessible(Maze m) //std::cout<<std::endl<<"perso: "<<m.getPosPlayer()<<std::endl<< "BOX:";
{

    std::vector<bool> marque;
    marque.resize(m.getField().size(),false);
    std::queue<unsigned short> file;
    unsigned short position=m.getPosPlayer();//std::cout<<std::endl<<"pos2:  "<<m.getField().size()<<std::endl;
    marque[position]=true;
    file.push(position);

    while(!file.empty())
    {
        position=file.front();

        if(m.isSquareWalkable(position+m.getCol())&&!marque[position+m.getCol()])
        {
            file.push(position+m.getCol());
            marque[position+m.getCol()]=true;

        }
        if(m.isSquareWalkable(position-m.getCol())&&!marque[position-m.getCol()])
        {
            file.push(position-m.getCol());
            marque[position-m.getCol()]=true;

        }
        if(m.isSquareWalkable(position+1)&&!marque[position+1])
        {
            file.push(position+1);
            marque[position+1]=true;

        }
        if(m.isSquareWalkable(position-1)&&!marque[position-1])
        {
            file.push(position-1);
            marque[position-1]=true;

        }
        file.pop();




    }
    /* for(int i=0;i<vec.size();i++){
         if(vec[i])
             std::cout<<i<<" ";}*/

    // std::cout<<std::endl;
    return marque;


}


std::vector<unsigned short> util::relier_point(Maze m, std::vector <unsigned short> vec)
{

    std::vector<unsigned short> resolution, origin,temp, box=m.getPosBoxes();

    std::queue <unsigned short>  file_position;
    std::queue <std::vector<unsigned char>> file_field;
    util u;
    std::vector <unsigned char> field=m.getField();
    unsigned short position=vec[0],c,b,v;
    vider(file_field);
    vider(file_position);
    marque_field.resize(0);
    marque_position.resize(0);
    origin.resize(0);
    file_position.push(position);
    file_field.push(field);
    marque_field.push_back(field);
    marque_position.push_back(position);

    bool win;



    for(int i=0; i<vec.size()-1; i++)
    {

        origin.resize(0);
        win=false;
        u.vider(file_field);
        u.vider(file_position);
        file_position.push(vec[i]);
        file_field.push(m.getField());


        origin.push_back(0);
        origin.push_back(4);
        c=0;


        while(!win)
        {

            position=file_position.front();
            field=file_field.front();
            m.change_etat_jeu(field,position);



            if(position==vec[i+1])
                win=true;
            // std::cout<<std::endl<<"vec: "<<vec[i]<<"  vec+1:  "<<vec[i+1]<<"position:  "<<m.getPosPlayer()<<std::endl;

            if(!m.isSquareWall(position-m.getCol())&&!win)
            {
                if(!m.isSquareBox(position-m.getCol())||(position-m.getCol()==vec[i+1]))
                {
                    m.updatePlayer(TOP);
                    if(!compare(m.getField(),m.getPosPlayer()))
                    {
                        if(m.getPosPlayer()==vec[i+1])
                        {
                            win=true;
                        }

                        file_field.push(m.getField());
                        file_position.push(m.getPosPlayer());
                        marque_field.push_back(m.getField());
                        marque_position.push_back(m.getPosPlayer());
                        origin.push_back(c);
                        origin.push_back(0);

                    }
                }
                if (!win)
                    m.change_etat_jeu(field,position);
            }

            if(!m.isSquareWall(position+m.getCol())&&!win)
            {
                if(!m.isSquareBox(position+m.getCol())||(position+m.getCol()==vec[i+1]))
                {
                    m.updatePlayer(BOTTOM);
                    if(!compare(m.getField(),m.getPosPlayer()))
                    {
                        if(m.getPosPlayer()==vec[i+1])
                        {
                            win=true;
                        }

                        file_field.push(m.getField());
                        file_position.push(m.getPosPlayer());
                        marque_field.push_back(m.getField());
                        marque_position.push_back(m.getPosPlayer());
                        origin.push_back(c);
                        origin.push_back(1);

                    }
                }
                if (!win)
                    m.change_etat_jeu(field,position);
            }

            if(!m.isSquareWall(position-1)&&!win)
            {
                if(!m.isSquareBox(position-1)||(position-1==vec[i+1]))
                {
                    m.updatePlayer(LEFT);
                    if(!compare(m.getField(),m.getPosPlayer()))
                    {
                        if(m.getPosPlayer()==vec[i+1])
                        {
                            win=true;
                        }

                        file_field.push(m.getField());
                        file_position.push(m.getPosPlayer());
                        marque_field.push_back(m.getField());
                        marque_position.push_back(m.getPosPlayer());
                        origin.push_back(c);
                        origin.push_back(2);

                    }
                }
                if (!win)
                    m.change_etat_jeu(field,position);
            }

            if(!m.isSquareWall(position+1)&&!win)
            {
                if(!m.isSquareBox(position+1)||(position+1==vec[i+1]))
                {
                    m.updatePlayer(RIGHT);
                    if(!compare(m.getField(),m.getPosPlayer()))
                    {
                        if(m.getPosPlayer()==vec[i+1])
                        {
                            win=true;
                        }

                        file_field.push(m.getField());
                        file_position.push(m.getPosPlayer());
                        marque_field.push_back(m.getField());
                        marque_position.push_back(m.getPosPlayer());
                        origin.push_back(c);
                        origin.push_back(3);

                    }
                }
                if (!win)
                    m.change_etat_jeu(field,position);
            }



            file_field.pop();
            file_position.pop();
            c=c+2;

        }
        //
        c=origin.size()-2;
        /* std::cout<<"origin:  ";
         for(int a=0; a<origin.size(); a++)
             std::cout<<origin[a];*/
        temp.resize(0);

        while(origin[c+1]!=4)
        {
            temp.push_back(origin[c+1]);
            c=origin[c];

        }

        invert(temp);
        for(int h=0; h<temp.size(); h++)
            resolution.push_back(temp[h]);
    }

    return resolution;





}


void util::invert(std::vector<unsigned short> &vec)
{
    std::vector<unsigned short> vec2;
    vec2=vec;
    vec.resize(0);
    for(int i=vec2.size()-1; i>=0; i=i-1)
    {
        vec.push_back(vec2[i]);
    }
}


bool util::compare(std::vector<unsigned char> vec,unsigned short a)
{
    bool ok=false;
    for(int i=0; i<marque_field.size(); i++)
    {
        if(vec==marque_field[i]&&a==marque_position[i])
        {
            ok=true;


        }

    }


    return ok;
}



/**
 * Permet de choisir un niveau a jouer. Renvoit le chemin du niveau en String
 * @return renvoit le chemin du niveau
 */
std::string util::choose_level()
{
    std::string path;
    unsigned short a,b;
    float c;

    std::ostringstream oss;
    Console::getInstance()->setColor(_COLOR_RED);
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<<"choose a level:";
    Console::getInstance()->setColor(_COLOR_YELLOW);
    std::cout<<std::endl<<"easy 1: 11"<<std::endl<<"easy 2: 12"<<std::endl<<"easy 3: 13"<<std::endl<<"easy 4: 14"<<std::endl<<"easy 5: 15"<<std::endl;
    std::cout<<"easy 6: 16"<<std::endl<<"easy 7: 17"<<std::endl<<"easy 8: 18"<<std::endl<<"easy 9: 19"<<std::endl<<"easy 10: 110"<<std::endl<<std::endl;
    Console::getInstance()->setColor(_COLOR_BLUE);
    std::cout<<"medium 1: 21"<<std::endl<<"medium 2: 22"<<std::endl<<"medium 3: 23"<<std::endl<<std::endl;
    Console::getInstance()->setColor(_COLOR_GREEN);
    std::cout<<"hard 1: 31"<<std::endl<<"hard 2: 32"<<std::endl<<"hard 3: 33"<<std::endl<<std::endl;
    Console::getInstance()->setColor(_COLOR_PURPLE);
    std::cout<<"test 1: 41"<<std::endl<<"test 2: 42"<<std::endl<<"test 3: 43"<<std::endl<<std::endl;
    Console::getInstance()->setColor(_COLOR_WHITE);


    std::cout<<"level: ";
    std::cin>>a;
    std::cout<<std::endl<<std::endl;
    path="./levels/";
    b=a/10;
    c=a;
    c=c/10;
    if(b==1)
    {
        path=path+"easy/easy_";
    }
    if(b==2)
    {
        path=path+"medium/medium_";
    }
    if(b==3)
    {
        path=path+"hard/hard_";
    }
    if(b==4)
    {

        path=path+"test/test_";

    }

    if(a!=110)
    {
        c=round( 10*(c-floor(c)));
        oss<<c;

        path=path+oss.str();

    }

    if(a==110)
        path="./levels/easy_10";
    path=path+".dat";
    std::cout<<path<<std::endl;
    std::ifstream fichier(path.c_str());




    return path;

}



void util::dispVector( std::vector<bool> vec, Maze maze )
{
    for(int i=0; i<vec.size(); i++)
    {
        Console::getInstance()->setColor(_COLOR_RED);

        if(vec[i]==false)
            Console::getInstance()->setColor(_COLOR_WHITE);


        if(i==maze.getPosPlayer())
            Console::getInstance()->setColor(_COLOR_GREEN);




        std::cout<<vec[i]<<" ";
        if((i+1)%maze.getCol()==0)
            std::cout<<std::endl;

    }
    std::cout<<std::endl;

}

