#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED
/**
 * \file note.h
 * \brief declaration of the class note
 * \author Romain Michau
 * \version 2.1
 */

#include <vector>

/** \class Note
 *  Represent a note gived to a node.
 *  higher is the note, best is a case (in theory)
 */
class Note
{
private:
    int note_distance_box;/**< Note gived for the distance beetween all the box and goals (or pivot) */
    int note_caisse_place;/**< Note for boxes which are already placed */
    int note_total; /**< Total note of the node */
    int coefA; /**< coef A (used for calcul total) */
    int coefB; /**< coef B (used for calcul total) */
    int refValue; /**< A value of reference (used for calcul total) */

public:

    /** \brief Constructor of the class Note
     *
     * \param coefA: coef A
     * \param coefb: coef B
     * \param refValue: ref value
     *
     */
    Note(int coefA,int coefb,int refValue);

    /** \brief Default constructor for class Note
     *
     */
    Note();


    /** \brief Destructor for class Note
     *
     */
    ~Note();

    /** \brief Return the total note of the node
     *
     * \return total note
     *
     */
    int get_note_total() ;

    /** \brief Getter of note_distance_box(
     *
     * \return note_distance_box
     *
     */
    int get_note_distance_box() ;

    /** \brief Getter of note_caisse_place
     *
     * \return note_caisse_place
     *
     */
    int get_note_caisse_place() ;

    /** \brief Setter of note_total
     *
     */
    void set_note_total(int total);

    /** \brief Setter of note_distance_box
     *
     * \param new note_distance_box
     *
     */
    void set_note_distance_box(int note);

    /** \brief Setter of note caisse place
     *
     * \param new note_caisse_place
     */
    void set_note_caisse_place(int note);

    /** \brief Calcul the total note
     *
     */
    void calculTotal();


};
#endif // NOTE_H_INCLUDED
