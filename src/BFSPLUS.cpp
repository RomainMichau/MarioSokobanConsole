#include "BFSPLUS.h"
#include "maze.h"
#include "heuristique.h"
#include "util.h"
#include "case_morte.h"
#include <vector>
BFSPLUS::BFSPLUS()
{
    //ctor
}

BFSPLUS::~BFSPLUS()
{
    //dtor
}

void BFSPLUS::reinit()
{
    util u;
    resolution.resize(0);
    chemin.resize(0);
    file_position.resize(0);
    file_note.resize(0);
    file_field.resize(0);
    file_classement.resize(0);
    marque_field.resize(0);
    origin.resize(0);

}


std::vector<unsigned char> BFSPLUS::bfs_malin(Maze m, bool dynDeadLocks,int &noeudvisite,int noteA,int noteB,int plafond)  //plafond: nombre de noeud max a explor� avant abandon
{
    std::vector<unsigned short>  vec;
    std::vector<bool> zone_accessible;
    std::vector<bool> new_zone_accessible;
    heuristique h;
    int position_player_or=m.getPosPlayer();
    int a=0;
    int b=0;
    int cpt=0;
    int c=0;
    util u;
    unsigned short newPositionOfBox,rang=0,pos_originel=m.getPosPlayer();
    Note note;
    bool stop_urgent=false;
    int num_position=0;
    std::vector<unsigned char> field=m.getField(),field_originel=m.getField();
    std::vector<unsigned short> position_box_or=m.getPosBoxes();
    bool win = false;
    unsigned short classement,position;
    std::vector<bool> zone_originel=u.zone_accessible(m);
    file_field.push_back(m.getField());
    file_position.push_back(zone_originel);
    file_note.push_back(h.heuristiquemaline(m,noteA,noteB,-1));
    file_classement.push_back(0);
    file_profondeur.push_back(0);
    unsigned profondeur;
    marque_field.push_back(field);
    int AScpt1=0;
    int AScpt2=0;

    origin.resize(2);
    case_morte dead;
    origin[0]=0;
    origin[1]=4444;
    unsigned short poto=0;


    while(!win&&!file_classement.empty()&&!stop_urgent)
    {
        poto++;


        if(marque_field.size()>plafond)
        {
            noeudvisite=666666;
            return chemin;
        }

        profondeur=file_profondeur.back();
        field=file_field.back();
        zone_accessible=file_position.back();
        c=file_classement.back();

        m.change_etat_jeu(field,zone_accessible);
        position_box_or=m.getPosBoxes();

        for(int i=0; i<m.getPosBoxes().size(); i++)
        {
            if(!win&&zone_accessible[position_box_or[i]+m.getCol()]&&(m._canPushBox(position_box_or[i],TOP,newPositionOfBox)&&!m.isSquareDeadSquare(position_box_or[i]-m.getCol())))
            {
                //DANS CE VAS LE JOUEUR POUSSE LA CAISSE VERS LE HAUT
                if(dynDeadLocks||!dead.dyn_dead(m,position_box_or[i]+m.getCol(),TOP))
                {

                    m.setPlayerPos(position_box_or[i]+m.getCol());

                    win=m.updatePlayer(TOP);
                    if(!compare(m.getField()))   //On verifie que ce cas n'a pas deja etait trait�
                    {

                        if((m.isSquareWalkable(m.getPosPlayer()+1)&&!m.isSquareWalkable(m.getPosPlayer()+m.getCol()+1))||(m.isSquareWalkable(m.getPosPlayer()-1)&&!m.isSquareWalkable(m.getPosPlayer()+m.getCol()-1)
                                                                                                                         )||(!m.isSquareWalkable(m.getPosPlayer()+1)&&m.isSquareWalkable(m.getPosPlayer()+2*m.getCol()+1))||(!m.isSquareWalkable(m.getPosPlayer()-1)&&m.isSquareWalkable(m.getPosPlayer()+2*m.getCol()-1)))
                        {

                            new_zone_accessible=u.zone_accessible(m);
                            note=h.heuristiquemaline(m,noteA,noteB,-1);

                            AScpt1++;
                        }
                        else
                        {
                            new_zone_accessible=zone_accessible;
                            new_zone_accessible[m.getPosPlayer()]=true;
                            new_zone_accessible[m.getPosBoxes()[i]]=false;
                            note=h.heuristiquemaline(m,noteA,noteB,i);


                            AScpt2++;
                        }


                        rang=u.rang(file_note,note);
                        file_note.insert(file_note.begin()+rang,note);
                        file_profondeur.insert(file_profondeur.begin()+rang,profondeur+1);



                        file_position.insert(file_position.begin()+rang,new_zone_accessible);
                        //      u.dispVector(u.zone_accessible(m),m);
                    //    u.insere(file_field,rang,m.getField());
                        file_field.insert(file_field.begin()+rang,m.getField());
                        marque_field.push_back(m.getField());

                        origin.push_back(c);
                        origin.push_back(position_box_or[i]+m.getCol());
                        file_classement.insert(file_classement.begin()+rang,origin.size());
                        origin.push_back(origin.size()-2);
                        origin.push_back(position_box_or[i]);

                    }
                    m.change_etat_jeu(field,zone_accessible);

                }
            }

            if(!win&&zone_accessible[position_box_or[i]-m.getCol()]&&(m._canPushBox(position_box_or[i],BOTTOM,newPositionOfBox)&&!m.isSquareDeadSquare(position_box_or[i]+m.getCol())))
            {
                //DANS CE VAS LE JOUEUR POUSSE LA CAISSE VERS LE BAS

                if(dynDeadLocks||!dead.dyn_dead(m,position_box_or[i]-m.getCol(),BOTTOM))
                {
                    m.setPlayerPos(position_box_or[i]-m.getCol());
                    win=m.updatePlayer(BOTTOM); //
                    if(!compare(m.getField()))
                    {


                        if((m.isSquareWalkable(m.getPosPlayer()+1)&&!m.isSquareWalkable(m.getPosPlayer()-m.getCol()+1))||(m.isSquareWalkable(m.getPosPlayer()-1)&&!m.isSquareWalkable(m.getPosPlayer()-m.getCol()-1)
                                                                                                                         )||(!m.isSquareWalkable(m.getPosPlayer()+1)&&m.isSquareWalkable(m.getPosPlayer()+m.getCol()+1))||(!m.isSquareWalkable(m.getPosPlayer()-1)&&m.isSquareWalkable(m.getPosPlayer()+m.getCol()-1)))
                        {
                            new_zone_accessible=u.zone_accessible(m);
                            note=h.heuristiquemaline(m,noteA,noteB,-1);
                            AScpt1++;
                        }
                        else
                        {
                            new_zone_accessible=zone_accessible;
                            new_zone_accessible[m.getPosPlayer()]=true;
                            new_zone_accessible[m.getPosBoxes()[i]]=false;
                            note=h.heuristiquemaline(m,noteA,noteB,i);

                            AScpt2++;
                        }

                        rang=u.rang(file_note,note);
                        file_note.insert(file_note.begin()+rang,note);
                        file_profondeur.insert(file_profondeur.begin()+rang,profondeur+1);

                        file_position.insert(file_position.begin()+rang,new_zone_accessible);
                        file_field.insert(file_field.begin()+rang,m.getField());
                        marque_field.push_back(m.getField());

                        origin.push_back(c);
                        origin.push_back(position_box_or[i]-m.getCol());
                        file_classement.insert(file_classement.begin()+rang,origin.size());
                        origin.push_back(origin.size()-2);
                        origin.push_back(position_box_or[i]);

                    }
                    m.change_etat_jeu(field,zone_accessible);
                }
            }

            if(!win&&zone_accessible[position_box_or[i]+1]&&(m._canPushBox(position_box_or[i],LEFT,newPositionOfBox)&&!m.isSquareDeadSquare(position_box_or[i]-1)))
            {
                /**DANS CE VAS LE JOUEUR POUSSE LA CAISSE VERS LE Gauche */

                if(dynDeadLocks||!dead.dyn_dead(m,position_box_or[i]+1,LEFT))
                {
                    m.setPlayerPos(position_box_or[i]+1);

                    win=m.updatePlayer(LEFT);
                    if(!compare(m.getField()))
                    {
                        if((m.isSquareWalkable(m.getPosPlayer()+m.getCol())&&!m.isSquareWalkable(m.getPosPlayer()+m.getCol()+1))||(m.isSquareWalkable(m.getPosPlayer()-m.getCol())&&
                                !m.isSquareWalkable(m.getPosPlayer()-m.getCol()+1))
                                ||                           (!m.isSquareWalkable(m.getPosPlayer()+m.getCol())&&m.isSquareWalkable(m.getPosPlayer()+m.getCol()+2))||(!m.isSquareWalkable(m.getPosPlayer()-m.getCol())&&
                                        m.isSquareWalkable(m.getPosPlayer()-m.getCol()+2)))
                        {
                            new_zone_accessible=u.zone_accessible(m);
                            AScpt1++;
                            note=h.heuristiquemaline(m,noteA,noteB,-1);

                        }
                        else
                        {
                            new_zone_accessible=zone_accessible;
                            new_zone_accessible[m.getPosPlayer()]=true;
                            new_zone_accessible[m.getPosBoxes()[i]]=false;
                            note=h.heuristiquemaline(m,noteA,noteB,i);

                            AScpt2++;
                        }


                        rang=u.rang(file_note,note);
                        file_note.insert(file_note.begin()+rang,note);
                        file_profondeur.insert(file_profondeur.begin()+rang,profondeur+1);



                        file_position.insert(file_position.begin()+rang,new_zone_accessible);
                        file_field.insert(file_field.begin()+rang,m.getField());
                        marque_field.push_back(m.getField());

                        origin.push_back(c);
                        origin.push_back(position_box_or[i]+1);
                        file_classement.insert(file_classement.begin()+rang,origin.size());
                        origin.push_back(origin.size()-2);
                        origin.push_back(position_box_or[i]);

                    }
                    m.change_etat_jeu(field,zone_accessible);
                }
            }



            if(!win&&zone_accessible[position_box_or[i]-1]&&(m._canPushBox(position_box_or[i],RIGHT,newPositionOfBox)&&!m.isSquareDeadSquare(position_box_or[i]+1)))
            {
                if(dynDeadLocks||!dead.dyn_dead(m,position_box_or[i]-1,RIGHT))
                {
                    m.setPlayerPos(position_box_or[i]-1);
                    win=m.updatePlayer(RIGHT);// std::cout<<std::endl<<"ALERT3"<<std::endl<<std::endl;
                    if(!compare(m.getField()))
                    {



                        if((m.isSquareWalkable(m.getPosPlayer()+m.getCol())&&!m.isSquareWalkable(m.getPosPlayer()+m.getCol()-1))||(m.isSquareWalkable(m.getPosPlayer()-m.getCol())&&
                                !m.isSquareWalkable(m.getPosPlayer()-m.getCol()-1))||
                                (!m.isSquareWalkable(m.getPosPlayer()+m.getCol())&&m.isSquareWalkable(m.getPosPlayer()+m.getCol()+1))||(!m.isSquareWalkable(m.getPosPlayer()-m.getCol())&&
                                        m.isSquareWalkable(m.getPosPlayer()-m.getCol()+1)))
                        {
                            new_zone_accessible=u.zone_accessible(m);
                            note=h.heuristiquemaline(m,noteA,noteB,-1);
                            AScpt1++;
                        }
                        else
                        {
                            new_zone_accessible=zone_accessible;
                            new_zone_accessible[m.getPosPlayer()]=true;
                            new_zone_accessible[m.getPosBoxes()[i]]=false;
                            note=h.heuristiquemaline(m,noteA,noteB,i);

                            AScpt2++;
                        }

                        rang=u.rang(file_note,note);
                        file_note.insert(file_note.begin()+rang,note);
                        file_profondeur.insert(file_profondeur.begin()+rang,profondeur+1);
                        file_position.insert(file_position.begin()+rang,new_zone_accessible);
                        file_field.insert(file_field.begin()+rang,m.getField());
                        marque_field.push_back(m.getField());

                        origin.push_back(c);
                        origin.push_back(position_box_or[i]-1);
                        file_classement.insert(file_classement.begin()+rang,origin.size());
                        origin.push_back(origin.size()-2);
                        origin.push_back(position_box_or[i]);
                    }
                    m.change_etat_jeu(field,zone_accessible);
                }
            }
        }
        file_classement.pop_back();
        file_position.pop_back();
        file_note.pop_back();
        file_field.pop_back();
        file_profondeur.pop_back();

    }


    c=origin.size()-2;
    b=0;

    while(origin[c+1]!=4444)
    {
        resolution.push_back(origin[c+1]);
        c=origin[c];
        b++;
    }

    m.change_etat_jeu(field_originel,zone_originel);

    resolution.push_back(pos_originel);
    invert(resolution);

    resolution=u.relier_point(m,resolution);
    if(!stop_urgent)
        chemin=m.convert(resolution);

    if(stop_urgent)
    {
        std::cout<<std::endl<<"SOLVER STOP, BFS++ FAIL"<<std::endl;
        chemin.push_back('s');
    }
    noeudvisite=marque_field.size();
    // std::cout<<"cpt1:"<<AScpt1<<"  cpt2:"<<AScpt2;
    return chemin;
}

void BFSPLUS::invert(std::vector<unsigned short> &vec)
{
    std::vector<unsigned short> vec2;
    vec2=vec;
    vec.resize(0);
    for(int i=vec2.size()-1; i>=0; i=i-1)
    {
        vec.push_back(vec2[i]);
    }
}


bool BFSPLUS::compare(std::vector<unsigned char> vec)
{
    return marque_field.exist(vec);
}















