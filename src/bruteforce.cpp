#include "bruteforce.h"
#include "maze.h"
#include "../utils/console.h"
#include "../utils/coord.h"

#include <iostream>
#include <queue>
Bruteforce::Bruteforce()
:m_cpt(1){
    //ctor
}

Bruteforce::~Bruteforce()
{
    //dtor
}


std::vector<unsigned char> Bruteforce::forcage(Maze m){
int direction=0;
bool win=false;
char dir=TOP;
std::vector<unsigned char> field=m.getField();
std::vector<unsigned short> position_box_or=m.getPosBoxes();
unsigned short a=0;
bool diz=0, stop_urgent=0;
int position__player_or=m.getPosPlayer();
resolution.resize(m_cpt,0);

while(win==0&&!stop_urgent){

        m.setField(field);
        m.setPlayerPos(position__player_or);
        m.setPosBoxes(position_box_or);
       // std::cout<<".";

  //3  std::cout<<std::endl;
        for(int i=0;i<resolution.size();i++){

          //  std::cout<<resolution[i]<<"-";
            if(resolution[i]==0)
                dir=TOP;
            if(resolution[i]==1)
                dir=BOTTOM;
            if(resolution[i]==2)
                dir=LEFT;
            if(resolution[i]==3)
            dir=RIGHT;
            win = m.updatePlayer(dir);}

            a=0;
        if(!win){
            while(resolution[a]==3&&a!=resolution.size()){
                a++;
            }
            if(a==resolution.size()){
                m_cpt++;
                resolution.resize(m_cpt);

                for(int i=0;i<resolution.size();i++){
                    resolution[i]=0;
                }
            }
            else{
                diz=0;
                resolution[0]++;
                if (resolution[0]==4)
                {
                    resolution[0]=0;
                    diz=1;
                }

                if(diz){
                for(int i=1;i<resolution.size();i++)
                {
                    if(diz){
                        diz=0;
                        resolution[i]++;
                        if (resolution[i]==4){
                            diz=!diz;
                            resolution[i]=0;
                        }

                        }

                }}
            }


        }






}if(!stop_urgent)
chemin=m.convert(resolution);
if(stop_urgent){
    std::cout<<std::endl<<"SOLVER STOP, BRUTEFORCE FAIL "<<std::endl;
    chemin.push_back('s');
}

std::cout<<std::endl;
return chemin;



}









