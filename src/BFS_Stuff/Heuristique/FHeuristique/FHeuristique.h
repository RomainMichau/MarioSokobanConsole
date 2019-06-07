/**
 * \file FHeurisitique.cpp
 * \brief declaration of the class FHeurisitique
 * \author Romain Michau
 * \version 2.1
 */

#ifndef FHEURISTIQUE_H
#define FHEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
#include "src/BFS_Stuff/Heuristique/HeuristiqueObjects/HeuristiqueClassique.h"
#include <unordered_map>
/** \class FHeuristique
* \brief Factory de l'heuristique
*
* methode getInstance renvoit:
**	HeuritiquePivot si il s'agit d'un niveau avec une possiblité d'appliqer une heurtique pivot
**	sinon Heuristique classique
*/
class FHeuristique
{

private:

    Maze *m; /**< Maze */
    Util u; /**< Util class */

public:
    /** \brief Construcor of the class FHeuristique
     *
     * \param m the Maze
     * \param coefA: used for notation of Notes
     * \param coefB:  used for notation of Notes
     *
     */
    FHeuristique(Maze *m, short coefA, short coefB) ;

    /** \brief Destructor of the class FHeuristique
     *
     */
    virtual ~FHeuristique();

    /**
    * \brief Determine and return the most appropriate type of Heurisitique to use
    *
    * return the most appropriate tpye of heurisitque in function of the MAze
    *	Pivot Heuritique
    *	or
    *	Classical Heuristique
    * \return the most appropriate type of Heurisitique to use
    */
    AHeuristique* getInstance();


    /** \brief Return a pointer on an instance of HeuristiqueClassique
     *
     * \return a pointer on an instance of HeuristiqueClassique
     *
     */
    HeuristiqueClassique* getClassicalHeuritique();


private:




    /** \brief return a frequentation Map of the Maze
     *
     * \return return a frequentation Map of the Maze
     *
     */
    std::vector<short> calcFrequentationSquares();

    /** \brief for each square calculate the distance with the nearest goal
     *
     * \return  a vector with for each square the distance to the nearest goal (in Box Movement)
     *
     */
    std::vector<short> calcMapDistanceFromNearestGoals();

    /**
    * \brief return the pivot point of the maze
    *
    * pivotPoint: the point with the most frequentation. \n
    * if there is many point with the same max frequentation, then the farest from goals win
    */
    short calcPivotPointPos(std::vector<short> distMap, std::vector<short> freqMap);


    /** \brief detect tunnels in the game
     *
     * tunnel is a path compose of a least two tunnelSquare
     * tunnelSquare: square which have only 2 walkable adjacent square. Each of this square must be in oppossite direction
     * \return a map: entryTunnelSquare => exitTunnelSquare
     */
    std::unordered_map<short,short> tunnelDetector();

    /**
    * \brief detect is the current Maze is a pivot level
    *
    * method to verify;
    *	for each box we checks that it need to pass throug the pivot to reach each goal
    *	1 exception:
    *		if the box if nearer from the goal than the pivot, then its
    * \return true if the level sent in parameters is indeed a pivot level
    */
    bool checkIfPivotLevel(short pivotPos);

    int coefA,coefB;/**< used for notation */


};


#endif // HEURISTIQUE_H
