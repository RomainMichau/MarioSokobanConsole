#include "maze.h"
#include "../utils/console.h"
#include "../utils/coord.h"
#include <fstream>
#include <iomanip>
#include "case_morte.h"

case_morte::case_morte()
    :nb_case_morte(0)
{
    //ctor
}

case_morte::~case_morte()
{
    //dtor
}


void case_morte::detect_dead(Maze &m)
{	
    unsigned short cote_mort=0;
    int hauteur_mort=0;
    unsigned short cote_mur=0;
    int hauteur_mur=0;
    int la_somme=0;
    int a,b;
    int evo=1;
    std::vector<unsigned char> field=m.getField();

    if(m.case_morte_activ== false)
    {
        m.case_morte_activ=true;


        for(int a=0; a<3; a++)
        {
            for(int i=1+m.getCol(); i<field.size(); i++)
            {

                if(m.isSquareDeadSquare(i-1))
                {
                    cote_mort++;
                }
                if(m.isSquareDeadSquare(i-m.getCol()))
                {
                    hauteur_mort++;
                }

                if(m.isSquareDeadSquare(i+m.getCol()))
                {
                    hauteur_mort++;

                }
                if(m.isSquareDeadSquare(i+1))
                {
                    cote_mort++;

                }


                if(m.isSquareWall(i-1))
                {
                    cote_mur++;
                }
                if(m.isSquareWall(i-m.getCol()))
                {
                    hauteur_mur++;
                }

                if(m.isSquareWall(i+m.getCol()))
                {
                    hauteur_mur++;

                }
                if(m.isSquareWall(i+1))
                {
                    cote_mur++;

                }

                la_somme=cote_mort+cote_mur+hauteur_mort+hauteur_mur;


                if(cote_mur>=1&&hauteur_mur>=1)
                {
                    if(field[i]!= SPRITE_WALL&&field[i]!= SPRITE_DEADSQUARE && field[i]!= SPRITE_GOAL && !m.isSquareBox(i) )
                    {
                        m.setSquare(i,9);
                        nb_case_morte++;
                        liste.push_back(i);
                        evo++;

                    }
                }

                cote_mort=0;
                hauteur_mort=0;
                cote_mur=0;
                hauteur_mur=0;
            }
        }

        for(int i=0; i<liste.size(); i++)
        {
            a=liste[i];
            b=a;
            a++;
            while(!m.isSquareGoal(a)&&!m.isSquareWall(a)&&!m.isSquareDeadSquare(a)&&!m.isSquareBox(a)&&!m.isSquareBoxPlaced(a)&&a<field.size()&&(m.isSquareWall(a+m.getCol())||m.isSquareWall(a-m.getCol())))
            {
                a++;
            }

            if(m.isSquareDeadSquare(a))
            {
                for(int c=b; c<a; c++)
                {
                    m.setSquare(c,9);

                }
            }

            a=b;
            a=a+m.getCol();

            while(!m.isSquareGoal(a)&&!m.isSquareWall(a)&&!m.isSquareDeadSquare(a)&&!m.isSquareBox(a)&&!m.isSquareBoxPlaced(a)&&a<field.size()&&(m.isSquareWall(a+1)||m.isSquareWall(a-1)))
            {
                a=a+m.getCol();
            }

            if(m.isSquareDeadSquare(a))
            {
                for(int c=b; c<a; c=c+m.getCol())
                {
                    m.setSquare(c,9);






                }
            }
        }
        /*for(int i=0;i<liste.size();i++)
            std::cout<<liste[i]<<"-";*/






    }
    else
    {
        m.case_morte_activ=false;

        for(int i=0; i<m.getField().size(); i++)
        {
            if(m.isSquareDeadSquare(i))
                m.setSquare(i,0);
        }




    }




}




bool case_morte::dyn_dead(Maze m, unsigned short position, unsigned char dir)
{
    unsigned short cote_d=0,cote_g=0,cote_h=0,cote_b=0,cote_hor=0,cote_ver=0;
    unsigned short position_box=0, position_futur=0,murd=0,murh=0,murg=0,murb=0,boxh=0,boxb=0,boxg=0,boxd=0;
    bool plz=false;
    bool tst;
   // std::cout<<"1";

    if(dir==TOP&&m.isSquareBoxNonPlaced(position-m.getCol())&&!m.isSquareGoal(position-2*m.getCol()))
    {

        position_box=position-m.getCol();
        position_futur=position_box-m.getCol();
    //    std::cout<<"pos"<<position_box<<"-";


//std::cout<<"2";
        if(!m.isSquareWalkable(position_futur-m.getCol()))
        {
            cote_h++;
            //cote_hor++;
           /* if(m.isSquareBoxNonPlaced(position_futur-m.getCol()))
                    boxh++;
                    if(m.isSquareWall(position_futur-m.getCol()))
            {
                murh++;
            }*/}
  //  std::cout<<"3";

    if(!m.isSquareWalkable(position_futur-1))
        {
            if(m.isSquareBoxNonPlaced(position_futur-1))
        {

            boxg++;
        }
        if(m.isSquareWall(position_futur-1))
        {
            murg++;
        }
        cote_g++;
        cote_ver++;
    }
    if(!m.isSquareWalkable(position_futur+1))
        {
            if(m.isSquareBoxNonPlaced(position_futur+1))
        {

            boxd++;
        }
        if(m.isSquareWall(position_futur+1))
        {
            murd++;
        }
        cote_d++;
        cote_ver++;
    }
}
if(dir==BOTTOM&&m.isSquareBoxNonPlaced(position+m.getCol())&&!m.isSquareGoal(position+2*m.getCol()))
    {
        position_box=position+m.getCol();
        position_futur=position_box+m.getCol();
        if(!m.isSquareWalkable(position_futur+m.getCol()))
        {
            if(m.isSquareBoxNonPlaced(position_futur+m.getCol()))
                    boxh++;
                    if(m.isSquareWall(position_futur+m.getCol()))
            {
                murb++;
            }
        cote_b++;
        cote_hor++;
    }

    if(!m.isSquareWalkable(position_futur-1))
        {
            cote_g++;
            cote_ver++;
            if(m.isSquareBoxNonPlaced(position_futur-1))
                    boxg++;
                     if(m.isSquareWall(position_futur-1))
            {
                murg++;
            }
    }
    if(!m.isSquareWalkable(position_futur+1))
        {
            if(m.isSquareBoxNonPlaced(position_futur+1))
        {

            boxd++;
        }
        if(m.isSquareWall(position_futur+1))
        {
            murd++;
        }
        cote_d++;
        cote_ver++;
    }
}

if(dir==LEFT&&m.isSquareBoxNonPlaced(position-1)&&!m.isSquareGoal(position-2))
    {
        position_box=position-1;
        position_futur=position_box-1;
        if(!m.isSquareWalkable(position_futur-m.getCol()))
        {
            if(m.isSquareBoxNonPlaced(position_futur-m.getCol()))
                    boxh++;
                   if(m.isSquareWall(position_futur-m.getCol()))
            {
                murh++;
            }
        cote_h++;
        cote_hor++;
    }

    if(!m.isSquareWalkable(position_futur-1))
        {
            cote_g++;
            cote_ver++;
            if(m.isSquareBoxNonPlaced(position_futur-1))
                    boxg++;
                     if(m.isSquareWall(position_futur-1))
            {
                murg++;
            }
    }
    if(!m.isSquareWalkable(position_futur+m.getCol()))
        {
            if(m.isSquareBoxNonPlaced(position_futur+m.getCol()))
                    boxh++;
                    if(m.isSquareWall(position_futur+m.getCol()))
            {
                murb++;
            }
        cote_b++;
        cote_hor++;
    }
}

if(dir==RIGHT&&m.isSquareBoxNonPlaced(position+1)&&!m.isSquareGoal(position+2))
    {
        position_box=position+1;
        position_futur=position_box+1;
        if(!m.isSquareWalkable(position_futur-m.getCol()))
        {
            if(m.isSquareBoxNonPlaced(position_futur-m.getCol()))
                    boxh++;

                    if(m.isSquareWall(position_futur-m.getCol()))
            {
                murh++;
            }
        cote_h++;
        cote_hor++;
    }

    if(!m.isSquareWalkable(position_futur+m.getCol()))
        {
            if(m.isSquareBoxNonPlaced(position_futur+m.getCol()))
                    boxb++;
                     if(m.isSquareWall(position_futur+m.getCol()))
            {
                murb++;
            }
        cote_b++;
        cote_hor++;
    }

    if(!m.isSquareWalkable(position_futur+1))
        {
            if(m.isSquareBoxNonPlaced(position_futur+1))
        {

            boxd++;
        }
        if(m.isSquareWall(position_futur+1))
        {
            murd++;
        }
        cote_d++;
        cote_ver++;
    }
}



if(cote_hor>=1&&cote_ver>=1)
    {

        if(cote_h>0&&cote_d>0&&(!m.isSquareWalkable(position_futur+1-m.getCol())))
            plz=true;

        if(cote_h&&cote_g&&(!m.isSquareWalkable(position_futur-1-m.getCol())))
            plz=true;

        if(cote_b&&cote_g&&(!m.isSquareWalkable(position_futur-1+m.getCol()))){
            plz=true;
           }

       if(cote_b&&cote_d&&(!m.isSquareWalkable(position_futur+1+m.getCol())))
            plz=true;

       if(boxb>0&&murd>0&&m.isSquareWall(position_futur-1+m.getCol()))
            plz=true;
        if(boxb>0&&murg>0&&m.isSquareWall(position_futur+1+m.getCol()))
            plz=true;
        if(boxh>0&&murg>0&&m.isSquareWall(position_futur+1-m.getCol()))
        plz=true;
      if(boxh>0&&murd>0&&m.isSquareWall(position_futur-1-m.getCol()))
            plz=true;
        if(boxg>0&&murb>0&&m.isSquareWall(position_futur-1-m.getCol())){

            }
        if(boxg>0&&murh>0&&m.isSquareWall(position_futur-1+m.getCol()))
            plz=true;
        if(boxd>0&&murh>0&&m.isSquareWall(position_futur+1+m.getCol()))
            plz=true;
        if(boxd>0&&murb>0&&m.isSquareWall(position_futur+1-m.getCol()))
            plz=true;


        if(murg>0&&m.isSquareWall(position_futur-2*m.getCol())&&m.isSquareWall(position_futur-m.getCol()-1)&&m.isSquareBoxNonPlaced(position_futur-m.getCol()+1)&&m.isSquareWall(position_futur-m.getCol()*2+1))
            plz=true;
        if(murh>0&&m.isSquareWall(position_futur-2)&&m.isSquareWall(position_futur-m.getCol()-1)&&m.isSquareBoxNonPlaced(position_futur+m.getCol()-1)&&m.isSquareWall(position_futur+m.getCol()-2))
            plz=true;
        if(murh>0&&m.isSquareWall(position_futur+2)&&m.isSquareWall(position_futur-m.getCol()+1)&&m.isSquareBoxNonPlaced(position_futur+m.getCol()+1)&&m.isSquareWall(position_futur+2+m.getCol()))
            plz=true;
        if(murd>0&&m.isSquareWall(position_futur-2*m.getCol())&&m.isSquareWall(position_futur-m.getCol()+1)&&m.isSquareBoxNonPlaced(position_futur-m.getCol()-1)&&m.isSquareWall(position_futur-1-2*m.getCol()))
            plz=true;
        if(murg>0&&m.isSquareWall(position_futur+2*m.getCol())&&m.isSquareWall(position_futur+m.getCol()-1)&&m.isSquareBoxNonPlaced(position_futur+m.getCol()+1)&&m.isSquareWall(position_futur+2*m.getCol()+1))
            plz=true;
        if(murb>0&&m.isSquareWall(position_futur-2)&&m.isSquareWall(position_futur+m.getCol()-1)&&m.isSquareBoxNonPlaced(position_futur-m.getCol()-1)&&m.isSquareWall(position_futur-2-m.getCol()))
             plz=true;
        if(murb>0&&m.isSquareWall(position_futur+2)&&m.isSquareWall(position_futur-m.getCol()+1)&&m.isSquareBoxNonPlaced(position_futur-m.getCol()+1)&&m.isSquareWall(position_futur-2-m.getCol()))
            plz=true;
            if(murd>0&&m.isSquareWall(position_futur+2*m.getCol())&&m.isSquareWall(position_futur+m.getCol()+1)&&m.isSquareBoxNonPlaced(position_futur+m.getCol()-1)&&m.isSquareWall(position_futur-1+2*m.getCol()))
            plz=true;

    }




 /*  if(plz){
    for(int i=0;i<m.getPosBoxes().size();i++)
        std::cout<<m.getPosBoxes()[i]<<"-";
        std::cout<<std::endl;
    std::cout<<"pos act:"<<position_box<<"   posfut"<<position_futur<<std::endl;
    std::cout<<"murh:"<<murh<<" murb:"<<murb<<" murg"<<murg<<" murd:"<<murd<<std::endl;
     std::cout<<"boxh:"<<boxh<<" boxb:"<<boxb<<" boxg"<<boxg<<" boxd:"<<boxd<<std::endl;}*/

    return plz;



}
