#include "DFS.h"
#include <queue>
#include "maze.h"
#include <vector>
#include <string>
#include "../utils/coord.h"
#include "util.h"
#include <iostream>
#include "../utils/console.h"
#include "../utils/coord.h"
#include <iostream>
#include <stdio.h>
DFS::DFS()

{
    //ctor
}

DFS::~DFS()
{
    //dtor
}


void DFS::reinit(){
util u;
resolution.resize(0);
chemin.resize(0);
u.vider(pile_position);
u.vider(pile_classement);
u.vider(pile_field);
marque_position.resize(0);
marque_field.resize(0);
origin.resize(0);




}

std::vector<unsigned char> DFS::letsgodfs(Maze m)


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

    bool win = false;
    bool done=false;

    pile_field.push(field);
    pile_position.push(u.zone_accessible(m));
    pile_classement.push(0);


    marque_position.push_back(u.zone_accessible(m));
    marque_field.push_back(field);
    zone_accessible=u.zone_accessible(m);
    origin.resize(2);
    bool stop_urgent =false;
    origin[0]=0;
    origin[1]=4444;


    while(!win&&!stop_urgent)
    {    field=pile_field.top();
    done =false;

        c=pile_classement.top();
         zone_accessible=pile_position.top();
        // std::cout<<std::endl<<"ALERT5"<<std::endl<<std::endl;
        m.change_etat_jeu(field,zone_accessible);
        position_box_or=m.getPosBoxes();







      for(int i=0;i<m.getPosBoxes().size();i++){

          //  std::cout<<std::endl<<"box"<<i<<" position:"<<position_box_or[i]<<std::endl;

        if(!done&&!win&&zone_accessible[position_box_or[i]+m.getCol()]&&(m._canPushBox(position_box_or[i],TOP,v)&&!m.isSquareDeadSquare(position_box_or[i]-m.getCol())))
        {

            m.setPlayerPos(position_box_or[i]+m.getCol());
            win=m.updatePlayer(TOP);
            if(!compare(m.getField(),u.zone_accessible(m)))
            { //std::cout<<std::endl<<"ALERT0"<<std::endl<<std::endl;
                pile_field.push(m.getField());
                done=true;
                pile_position.push(u.zone_accessible(m));
                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]+m.getCol());
                 pile_classement.push(origin.size());
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);




            }
            m.change_etat_jeu(field,zone_accessible);

        }

 if(!done&&!win&&zone_accessible[position_box_or[i]-m.getCol()]&&(m._canPushBox(position_box_or[i],BOTTOM,v)&&!m.isSquareDeadSquare(position_box_or[i]+m.getCol())))
        {
            m.setPlayerPos(position_box_or[i]-m.getCol());
            win=m.updatePlayer(BOTTOM); //
            if(!compare(m.getField(),u.zone_accessible(m)))
            {//std::cout<<std::endl<<"ALERT1"<<std::endl<<std::endl;
                pile_field.push(m.getField());
                done=true;
                pile_position.push(u.zone_accessible(m));

                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]-m.getCol());
                 pile_classement.push(origin.size());
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);

            }
            m.change_etat_jeu(field,zone_accessible);
        }

         if(!win&&zone_accessible[position_box_or[i]+1]&&(m._canPushBox(position_box_or[i],LEFT,v)&&!m.isSquareDeadSquare(position_box_or[i]-1)))
        {
            m.setPlayerPos(position_box_or[i]+1);

            win=m.updatePlayer(LEFT);
            if(!compare(m.getField(),u.zone_accessible(m)))
            {
                pile_field.push(m.getField());

                pile_position.push(u.zone_accessible(m));
                done=true;
                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                origin.push_back(position_box_or[i]+1);
                 pile_classement.push(origin.size());
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);

            }
            m.change_etat_jeu(field,zone_accessible);
        }



         if(!done&&!win&&zone_accessible[position_box_or[i]-1]&&(m._canPushBox(position_box_or[i],RIGHT,v)&&!m.isSquareDeadSquare(position_box_or[i]+1)))
        {
            m.setPlayerPos(position_box_or[i]-1);
            win=m.updatePlayer(RIGHT);// std::cout<<std::endl<<"ALERT3"<<std::endl<<std::endl;
            if(!compare(m.getField(),u.zone_accessible(m)))
            {
                pile_field.push(m.getField());
                pile_position.push(u.zone_accessible(m));

                marque_position.push_back(u.zone_accessible(m));
                marque_field.push_back(m.getField());
                origin.push_back(c);
                done=true;
                origin.push_back(position_box_or[i]-1);
                 pile_classement.push(origin.size());
                origin.push_back(origin.size()-2);
                origin.push_back(position_box_or[i]);

            }
            m.change_etat_jeu(field,zone_accessible);
        }


      }




                if(!done)
        {
            pile_position.pop();
            pile_field.pop();
            pile_classement.pop();

        }



    }

        if(!stop_urgent){
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
    chemin=m.convert(resolution);



std::cout<<std::endl<<"noeud visite: "<<marque_field.size();}

if(stop_urgent){
    std::cout<<std::endl<<"SOLVER STOP, DFS FAIL "<<std::endl;
    chemin.push_back('s');
}
    return chemin;
}


bool DFS::compare(std::vector<unsigned char> vec,std::vector<bool> a)
{
    bool ok=false;
    for(int i=0; i<marque_field.size(); i++)
    {
        if(vec==marque_field[i]&&a==marque_position[i])
           {ok=true;


           }

    }


    return ok;
}


void DFS::invert(std::vector<unsigned short> &vec)
{
    std::vector<unsigned short> vec2;
    vec2=vec;
    vec.resize(0);
    for(int i=vec2.size()-1; i>=0; i=i-1)
    {
        vec.push_back(vec2[i]);
    }
}

