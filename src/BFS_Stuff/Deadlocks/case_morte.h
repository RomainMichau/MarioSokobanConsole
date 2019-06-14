/**
 * \file case_morte.h
 * \brief declaration of the class case_morte
 * \author Romain Michau
 * \version 2.1
 */

#ifndef CASE_MORTE_H
#define CASE_MORTE_H
#include "src/Maze/Maze.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include "src/utils/util.h"
#include <fstream>
#include <iomanip>
#include <unordered_set>
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/Deadlocks/DeadlocksObjects/DynDeadLocks.h"


   /** \struct  VectorHash
     *  \brief foncteur for generaing hash of a std::unordered_set<unsigned short>
     */


/** \class Case_morte
 * \brief Contain tools for managging static and dynamic deadlocks
 *
 * Defintion: \n
 *  Static DL: it is a square from which it is impossible to push a box on any goal (example: corners) \n
 *  Dynamic DL: it is a node which will create an unsolvable situation becuause of boxes which blocks each other (example: square composed of 4 boxes)
 */
class Case_morte
{

     struct VectorHash
    {
        size_t operator()(const DynDeadLocks& dl) const
        {
			const short a= dl.getHash();
			return a;
        }
    };
private:
    Maze *m /**< Maze to work in */;
    Util u /**< Util class */;
    std::unordered_set<DynDeadLocks, VectorHash> knownDealocks; /**< Set of the known Dyn DL */
public:

    /** \brief Constrcutor of class Case_morte
     * \param m Maze on which the class is going to work
     */
    Case_morte(Maze *m);


    /** \brief Destructor of the class Case_morte
     */
    ~Case_morte();

    /** \brief Will detect static DL
     *  Will make a BFS for each square. If it cant reach a goal, then is it a deadlocls
     *  Will marque DL directly on the Maze
     *
     */
    void detect_static_DL();

    /** \brief Will detect dynamique Deadlocks on a Node
     *
     * Will also check if the current Node can only lead to other DL
     * Will marque new encoutterd DL
     * \param node: Node to work on
     * \return true if this is a DL
     *
     */
    bool detect_dyn_DL( Node *node);


    /** \brief Check if the node is marque as a DL
     *
     * \param node: node to check
     * \return true if it is marque as a DL
     *
     */
    bool isMarqueAsDL(Node *node);

private:

    /** \brief Detect if an aglomerate is a DL
     *
     * \param aglomerateBoxes aglomareate to check
     * \return true if it is a DL
     *
     */
    bool isADynDeadlock(Maze* m,std::unordered_set<unsigned short> aglomerateBoxes,short normPos);

};

#endif // CASE_MORTE_H
