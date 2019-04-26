#include "note.h"
#include <vector>


Note::Note(int cA,int cB,int reVal)
{
    coefA=cA;
    coefB=cB;
    refValue=reVal;
    note_total=0;
}
Note::Note()
{


}

Note::~Note()
{
}


int Note::get_note_total()
{
    return note_total;
}

int Note::get_note_caisse_place()
{
    return note_caisse_place;
}


int Note::get_note_distance_box()
{
    return note_distance_box;
}


std::vector<int> Note::get_note_distance_box_by_box()
{
    return note_distance_box_by_box;
}


void Note::set_note_total(int total)
{
    note_total=total;
}

void Note::set_note_distance_box(int note)
{
    note_distance_box=note;
}

void Note::set_note_caisse_place(int note)
{
    note_caisse_place=note;
}

void Note::set_note_distance_box_by_box(std::vector<int> note_by_caisse)
{
    note_distance_box_by_box=note_by_caisse;
}

void Note::calculTotal()
{
    note_total=refValue-(note_distance_box*coefA + note_caisse_place*coefB);
}

