#ifndef BFSPLUS_H
#define BFSPLUS_H
/**
 * \file BFSPLUS.h
 * \brief declaration of the class BFSPLUS
 * \author Romain Michau
 * \version 2.1
 */
#include <unordered_set>
#include <unordered_map>

#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include"src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"

/** \class  BFSPLUS
 *  \brief this class is the one which make the BFS itself
 *
 *  It is the central piece of the program, it will make call to other component
 */

class BFSPLUS
{

private:
    AHeuristique* heuristique; /**< The heuristique used to resolve the Maze (must inherit of AHeuristique)  */
    Maze *m; /**< The Maze */
    std::unordered_set<std::string>marque;/**< List of already encountered case */

private:

    /** \struct  BestBFSCase
    *   \brief concteur used to get the best cased first
    *
    *   will return the Node with the best Note
     */
    struct BestBFSCase
    {
        bool operator()(Node b1, Node b2) const
        {
            return b1.note.get_note_total() < b2.note.get_note_total();
        }
    };

    /** \brief Determine if the current state of m has already been treated
     *
     *  will marqued the case if it is a new one
     *
     * \param normalizePlayerPos: normalize position of the player
     * \return true if the case is already marqued
     *
     */
    bool marqued(short normalizePlayerPos);

public:

    /** \brief Consctructor of the class BFSPLUS
     *
     * \param m: Maze
     * \param heuristique; heuristique to use
     *
     */
    BFSPLUS(Maze *m,AHeuristique* heuristique);

    /** \brief Destructor of the class BFSPLUS
     *
     */
    virtual ~BFSPLUS();

    /** \brief will find a path to solve m
     *
     * \param &noeudvisite: reference which will take to value of the nb of node visited
     * \return a vector of char  representing the directions to take for solving the maze
     *
     */
    std::vector<unsigned char> runBFS(unsigned &noeudvisite);
};

#endif // BFSPLUS_H
