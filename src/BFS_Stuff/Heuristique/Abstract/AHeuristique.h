/**
 * \file AHeurisitique.h
 * \brief declaration of the class AHeurisitique
 * \author Romain Michau
 * \version 2.1
 */

#ifndef AHEURISTIQUE_H
#define AHEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/Heuristique/MacroMover/MacroMover.h"

#include <unordered_map>

/** \class  AHeuristique
 *  \brief Interface used for implemeting heurisitque class
 *
 *
 */

class AHeuristique
{



public:

    /** \brief Constructor of the interface AHeuristique
     *
     * \param m: Maze attributed to this class
     * \param coefA: coef used to calculated the note of each Node
     * \param coefB: coef used to calculated the note of each Node
     * \param isPivotHeuristique: true if the interface implement the class HeuristiquePivot
     *
     */
    AHeuristique(Maze *m, int coefA, int coefB, bool isPivotHeuristique);

    /** \brief Destructor of the class AHeuristique
     */
    virtual ~AHeuristique();

    /** \brief <b>pure virtual</b> function which calculate the note of the node sent in parameters
     *
     * \param node: to to Calculate the note
     * \param boxPushedID: id the box pushed during the move of the node
     * \param newPos short: new position of the box (after the move)
     */
    virtual void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos) = 0;


    /** \brief <b> pure virtual </b>function which return the name of the class implementing this interface
     *
     * \return the name of the class implementing this interface
     *
     */
    virtual std::string sayHello() = 0;

    /** \brief <b> Pure virtual </b> which return the list of all the chapters of the game
     *
     * \return the first chapter of the list (others can be access via the linked list system of the class Chapter)
     *
     */
    virtual Chapter* getChapters() = 0;


    /** \brief getter isPivotHeuristique
     *
     * \return true if is isPivotHeuristique
     *
     */
    virtual bool isPivotHeuristique()
    {
        return pivotHeuristique;
    };

   /** \brief <b>Pure Virtual </b>Manage macroMove
    *
    * \param caseTracker: list of the NodeRetrackInfo already find by the BFS
    * \param node: current Node
    * \param boxPosition: new posititon of the box after the move
    * \return a pair
    *
    */
    virtual std::pair<short, short> macroMove(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxPosition) = 0;
protected:


    Util u;/**< Classe used for small operation */
    Maze *m;/**< pointer to the maze */
    Note note;/**< Note class (used for give a note to nodes */
    Case_morte deadlocks; /**< Used for detect dynamics DL */
    MacroMover macroMover;/**< Macro Mover */
    bool pivotHeuristique;/**< true if implemented by HeuristiquePivot */

};


#endif // HEURISTIQUE_H
