#ifndef HEURISTIQUEC_H
#define HEURISTIQUEC_H
/**
 * \file HeuristiqueClassique.h
 * \brief declaration of the class HeuristiqueClassique
 * \author Romain Michau
 * \version 2.1
 */
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"

#include <unordered_map>

/** \class  HeuristiqueClassique
 *  \brief classical heuristique system
 */
class HeuristiqueClassique :public AHeuristique
{
    /** FHeuristique is firend for  factory design pattern need
     *
     */
    friend class FHeuristique;

public:

    /** \brief Will calculate the note of the node sent in parameter
     *
     * will directly put the note in the node itsel
     * \param node: node to note
     * \param boxPushedID: id of the box pushed during the node
     * \param newPos: new position of the box
     */
    void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos);

    /** \brief Destructor of the class  HeuristiqueClassique
     *
     */
    ~HeuristiqueClassique();


    /** \brief Return the name of the class
     *
     *<b>Herited from AHeuristique</b>
     * \return virtual the name of the class
     *
     */
    virtual std::string sayHello()
    {
        return "Classique Heuristique";
    };

    /** \brief all the chapter used, in this case this is NULL
     *
     * The classical Heuristique don't use chapter system
     * <b>Herited from AHeuristique</b>
     * \return NULL
     *
     */
    virtual Chapter* getChapters()
    {
        return NULL;
    };


    /** \brief Function that will make macromoved if needed <b> Will do nothing in the Classical Heuristique </b>
     *
     * \param std::vector<Node::NodeRetrackInfo>&caseTracker
     * \param node Node*
     * \param boxPosition short
     * \return virtual std::pair<short, short>
     *
     */
    virtual std::pair<short, short> macroMove(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxPosition)
    {
        return std::pair<short, short>(-1, -1);
    };

private:
    /** \brief Constructor of the class HeuristiqueClassique
     *
     * \param m: the maze
     * \param coefA: coef used for notation
     * \param coefB:coef used for notation
     *
     */
    HeuristiqueClassique(Maze *m, int coefA, int coefB);


    /** \brief Calcul the note of the distance box of the currend node
     *
     * \return the note
     *
     */
    unsigned short calc_note_distance_box_bfs_multiple_box();


};


#endif // HEURISTIQUE_H
