#ifndef UTIL_H
#define UTIL_H
/**
 * \file util.h
 * \brief declaration of the class util
 * \author Romain Michau
 * \version 2.1
 */
#include "src/Maze/Maze.h"
#include "src/utils/Coord.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/BFS_Stuff/BFS_Objects/Mother_Class/NodeCaseMother.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <unordered_set>

/** \class Util
 *
 *   \brief Contains a set of utilitary methodes
 */
class Util
{
    /** \class  BFSCase_relier_point
    *  \brief trackBFS Type of the BFS in relier_point(...)
    *       Represent a Node
    *
    *  used for retrcking operations and marquing operation of Util::relier_point(Maze  m, std::vector <unsigned short> positions)\n
    *  Inherits of NodeCaseMother
    */
    class BFSCase_relier_point :public  NodeCaseMother
    {
    public:

        /** \brief Constructor of class BFSCase_relier_point
         *
         * \param field: field of the Maze
         * \param pos:position of the player
         * \param id: id of the node
         * \param pId: id of the parent Node
         * \param dir: direction of the player
         *
         */
        BFSCase_relier_point(std::vector<unsigned char> field, unsigned short pos, int id, int pId, char dir)
            : NodeCaseMother(id, pId), field(field), position(pos), dir(dir) {};

        /** \brief Destructor of the class BFSCase_relier_point
         *
         */
        ~BFSCase_relier_point() {};

        std::vector<unsigned char> field;/**< Field of the maze */
        unsigned short position;/**< Position of the player */
        char dir;/**< Direction of the payer during this node */
    };
private:

    std::vector<BFSCase_relier_point> marque/**< Marqer vector for the function  Util::relier_point(...)*/;


    /** \brief Check if a BFSCase_relier_point is alredy marqed in marque
     *
     * \param tstCase: node to check
     * \return true if the node sent in paramters is already marqued
     *
     *  Will marqed the node if it is not already the case \n
     *  Function call in Util::relier_point(Maze  , std::vector <unsigned short> )
     */
    bool compare(BFSCase_relier_point tstCase);

    /** \brief Check if the couple nPos && positions of the box of the maze is already marqed in the set marqueZoneBFS
     *
     * \param nPos: normalize position of the player
     * \param m: Maze
     * \param marqueZoneBFS: set of already marqued Node
     * \return true if the couple is already marqued
     *
     *  This function is only called in Util::getPathSquareToSquareZoneMethod(const Maze * , short , short , short )

     */
    bool marqued(short nPos, const  Maze *m, std::unordered_set<std::string > &marqueZoneBFS);

    /** \brief Check if a file exist
     *
     * \param name: path of the file to check
     * \return true if the file exist
     *
     */
    bool file_exist(const std::string& filePath);

public:

    /** \brief Constructor of class Util
     *
     *
     */
    Util();


    /** \brief Destructor of class Util
     *
     *
     */
    ~Util();



public:
    /** \brief Empty the queue sent in parameter
     *
     * \param t: queue to Empty
     *
     */
    void vider(std::queue<unsigned short> &t);

    /** \brief Empty the queue sent in parameter
     *
     * \param t: queue to Empty
     *
     */
    void vider(std::queue<std::vector<unsigned char>> &t);

    /** \brief Empty the queue sent in parameter
     *
     * \param t: queue to Empty
     *
     */
    void vider(std::queue< BFSCase_relier_point> &queue);

    //return the pos of the boxes which are aglomerate to the box sent in parameters
    /** \brief Detect if an aglomerat of box exist around a box
     *
     * \param m: Maze
     * \param initBox: position of the box to check
     * \return a vector of all the box forming an aglomerat (the one sent in paramters will also be in this vector)
     *
     *  An aglomerat is when many box are touching each other
     */
    std::unordered_set<unsigned short> detectAgglomerateOFBoxes(Maze *m,short initBox);

    /** \brief Calculate the accissble Zone of the Maze
     *
     * \param m: Maze
     * \param normPos: normalize positions of the player
     * \return the accesible zone + the normalize position (in parameters)
     *
     *  The accesible zone is the zone that the player can reach without having to push a box \n
     *  The normalize Position is the most top and most left square that the player can reach \n
     */
    std::vector<bool> calcZoneAccessible(const Maze* m, short &normPos);

    /** \brief Will convert successive position in a vector of direction to take for reach all this positions
     *
     * \param m Maze
     * \param  positions: list of positions to reach
     * \return vector containing all the directions to follow
     *
     */
    std::vector<unsigned char> relier_point(Maze m, std::vector <unsigned short> positions);

    /** \brief Ask the player to choose a level
     *
     * \return the path of the level choose by the player
     *
     */
    std::string choose_level();

    /** \brief Calcul the path beetween a square and the neared Goal in BM
     *
     * \param m : Maze
     * \param squareID: square to find the path
     * \return Return the path beetween the squareID send in parameters and the nearest goal. \n Will return null if no possible path
     *
     *  BM: box movement (path is like a path if we push a box)
     */
    std::deque<short> getPathSquareToGoalBM(const Maze* m, short squareID);

    /** \brief Return the path beetween the squareID send in parameters and the toSquare.
     *
     * \param m: Maze*
     * \param fromSquare: begging square
     * \param toSquare: goal square
     * \return Return the path beetween the squareID send in parameters and the toSquare goal. \n  path is the id of all the square
     *
     *  BM: box movement (path is like a path if we push a box)
     */
    std::deque<short> getPathSquareToSquareBM(const Maze* m, short fromSquare, short toSquare);

    /** \brief return the path beewteen fromSquare and toSquare with BFSPlus like method
     *
     * \param m: Maze
     * \param fromSquare (must be accessible from posPlayer)
     * \param toSquare
     * \param posPlayer: position of the player
     * \return vector of NodeRetrackInfo representing all the node to take for retracing the path
     *
     */
    std::vector< Node::NodeRetrackInfo> getPathSquareToSquareZoneMethod(const Maze* m, short fromSquare, short toSquare, short posPlayer);

    /** \brief Return the path beetween 2 square in PM, ignore boxes
     *
     * Return the path beetween the fromSquare  send in parameters and the toSquare .
	 * If no possible path, return empty vector
	 * path is the id of all the square
     * \param m: Maze*
     * \param fromSquare
     * \param toSquare
     * \return vector of square representing the path beetween fromSquare nd twoSquare
     * PM: player like movement
     *
     */
    std::deque<short> getPathSquareToSquarePM(const Maze* m, short fromSquare, short toSquare);

    /** \brief return dist map of toSquare (in BM)
     *
     * \param m: Maze*
     * \param toSquare
     * \return distMap of toSquare
     *
     * a dist map is a vector of the size of the field, which for each square it has for value the distance from toSquare
     */
    std::vector<short>  getDistMapOfSquare(const Maze *m, short toSquare);

    /** \brief Display a vector of the size of the field
     *
     * \param m: Maze*
     * \param vec: vector to display
     * \return void
     *
     */
    void dispVector(const Maze* m, std::vector<short> vec);

    /** \brief Display a vector of the size of the field
     *
     * \param m: Maze*
     * \param vec: vector to display
     * \return void
     *
     */
    void dispVector(const Maze* m, std::vector<bool> vec);






};



#endif // UTIL_H
