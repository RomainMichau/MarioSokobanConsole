#include "BFS.h"
#include <queue>
#include "maze.h"
#include <vector>
#include <string>
#include "../utils/coord.h"
#include "util.h"
#include <iostream>
#include "stock_field.h"


BFS::BFS()

{
    //ctor
}

BFS::~BFS()
{
    //dtor
}

void BFS:: reinit(){
util u;
resolution.resize(0);
chemin.resize(0);
marque_position.resize(0);
u.vider(file_position);
u.vider(file_field);
marque_field.resize(0);
origin.resize(0);



}

std::vector<unsigned char> BFS::letsgobfs(Maze m)


{
       std::vector<unsigned short>  vec;
    int position_player_or=m.getPosPlayer();
    int a=0;
    int b=0;
    int c=0;
    util u;

    unsigned short v, pos_perso_or,pos_originel=m.getPosPlayer();
    int num_position=0;

    std::vector<unsigned char> field=m.getField(),field_originel=m.getField();
    std::vector<bool> zone_accessible;
    std::vector<unsigned short> position_box_or=m.getPosBoxes() ;
    std::vector<bool> zone_originel=u.zone_accessible(m);

    bool win = false, stop_urgent=false;

    file_field.push(field);
    file_position.push(u.zone_accessible(m));
    marque_position.push_back(u.zone_accessible(m));
    marque_field.push_back(field);
    zone_accessible=u.zone_accessible(m);
    origin.resize(2);
    origin[0]=0;
    origin[1]=4444;


    while(!win&&!stop_urgent)
    {    field=file_field.front();

         zone_accessible=file_position.front();
        // std::cout<<std::endl<<"ALERT5"<<std::endl<<std::endl;
        m.change_etat_jeu(field,zone_accessible);
        position_box_or=m.getPosBoxes();







      for(int i=0;i<m.getPosBoxes().size();i++){

          //  std::cout<<std::endl<<"box"<<i<<" position:"<<position_box_or[i]<<std::endl;

        if(!win&&zone_accessible[position_box_or[i]+m.getCol()]&&(m._canPushBox(position_box_or[i],TOP,v)&&!m.isSquareDeadSquare(position_box_or[i]-m.getCol())))
        {

            m.setPlayerPos(position_box_or[i]+m.getCol());
            win=m.updatePlayer(TOP);
            if(!compare(m.getField()))
            { //std::cout<<std::endl<<"ALERT0"<<std::endl<<std::endl;
                file_field.push(m.getField());
                file_position.push(u.zone_accessible(m));
                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]+m.getCol());
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);




            }
            m.change_etat_jeu(field,zone_accessible);

        }

 if(!win&&zone_accessible[position_box_or[i]-m.getCol()]&&(m._canPushBox(position_box_or[i],BOTTOM,v)&&!m.isSquareDeadSquare(position_box_or[i]+m.getCol())))
        {
            m.setPlayerPos(position_box_or[i]-m.getCol());
            win=m.updatePlayer(BOTTOM); //
            if(!compare(m.getField()))
            {//std::cout<<std::endl<<"ALERT1"<<std::endl<<std::endl;
                file_field.push(m.getField());
                file_position.push(u.zone_accessible(m));
                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]-m.getCol());
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);

            }
            m.change_etat_jeu(field,zone_accessible);
        }

         if(!win&&zone_accessible[position_box_or[i]+1]&&(m._canPushBox(position_box_or[i],LEFT,v)&&!m.isSquareDeadSquare(position_box_or[i]-1)))
        {
            m.setPlayerPos(position_box_or[i]+1);

            win=m.updatePlayer(LEFT);
            if(!compare(m.getField()))
            {
                file_field.push(m.getField());
                file_position.push(u.zone_accessible(m));
                marque_position.push_back(u.zone_accessible(m)); //oki
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]+1);
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);

            }
            m.change_etat_jeu(field,zone_accessible);
        }



         if(!win&&zone_accessible[position_box_or[i]-1]&&(m._canPushBox(position_box_or[i],RIGHT,v)&&!m.isSquareDeadSquare(position_box_or[i]+1)))
        {
            m.setPlayerPos(position_box_or[i]-1);
            win=m.updatePlayer(RIGHT);// std::cout<<std::endl<<"ALERT3"<<std::endl<<std::endl;
            if(!compare(m.getField()))
            {
                file_field.push(m.getField());
                file_position.push(u.zone_accessible(m));
                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]-1);
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);

            }
            m.change_etat_jeu(field,zone_accessible);
        }

      }
        file_field.pop();
        file_position.pop();
        c=c+4;


    }


    c=origin.size()-2;
    b=0;
  // std::cout<<std::endl<<"WIIIIINNNNNNNN"<<std::endl<<std::endl;

/*for(int i=0;i<origin.size();i++)
    std::cout<<origin[i]<<"-";*/




    while(origin[c+1]!=4444)
    {   resolution.push_back(origin[c+1]);
        c=origin[c];
        b++;
    }
m.change_etat_jeu(field_originel,zone_originel);

resolution.push_back(pos_originel);
    invert(resolution);
    resolution=u.relier_point(m,resolution);


  /*  std::cout<<std::endl<<std::endl<<"resolutinon: "<<std::endl;
    for(int i=0;i<resolution.size();i++)
    std::cout<<resolution[i]<<"-";*/
    if(!stop_urgent)
    {chemin=m.convert(resolution);}
    if(stop_urgent){
    std::cout<<std::endl<<"SOLVER STOP, BFS FAIL"<<std::endl;
    chemin.push_back('s');
}



std::cout<<std::endl<<"noeud visite: "<<marque_field.size();
    return chemin;
}


/*bool BFS::compare(std::vector<unsigned char> vec,std::vector<bool> a)
{
    bool ok=false;
    for(int i=0; i<marque_field.size(); i++)
    {
        if(vec==marque_field[i]&&a==marque_position[i])
           {ok=true;


           }

    }


    return ok;
}*/
bool BFS::compare(std::vector<unsigned char> vec)
{
return marque_field.exist(vec);
}

void BFS::invert(std::vector<unsigned short> &vec)
{
    std::vector<unsigned short> vec2;
    vec2=vec;
    vec.resize(0);
    for(int i=vec2.size()-1; i>=0; i=i-1)
    {
        vec.push_back(vec2[i]);
    }
}

