/**
 * \file note.h
 * \brief declaration of the class note
 * \author romain michau
 * \version 2.1
 */
#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED
#include <vector>


class Note
{
public:
    Note(int coefA,int coefb,int refValue);
    Note();
    ~Note();
    int get_note_total();
    int get_note_distance_box();
    int get_note_caisse_place();
    std::vector<int> get_note_distance_box_by_box();

    void set_note_total(int total);
    void set_note_distance_box(int note);
    void set_note_caisse_place(int note);
    void set_note_distance_box_by_box(std::vector<int> note_by_caisse);
    void calculTotal();

protected:


private:
    int note_distance_box;
    int note_caisse_place;
    std::vector<int> note_distance_box_by_box;
    int note_total;
    int coefA;
    int coefB;
    int refValue;

};
#endif // NOTE_H_INCLUDED
