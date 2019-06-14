/**
 * \file HeuristiquePivot.h
 * \brief declaration of the class HeuristiquePivot
 * \author Romain Michau
 * \version 2.1
 */
#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H
#include "src/Maze/Maze.h"
#include "src/BFS_Stuff/Heuristique/note.h"
#include "src/utils/Util.h"
#include "src/BFS_Stuff/BFS_Objects/Node.h"
#include "src/BFS_Stuff/DeadLocks/case_morte.h"
#include "src/BFS_Stuff/Heuristique/Abstract/AHeuristique.h"
#include "src/Maze/MazeMap.h"

#include <utility>
#include <unordered_map>
/**
*	\class HeuristiquePivot
*   \brief heuristique wich use a Pivot Point Method (see def below)
*
*	Method: \n
*       -A pivot point is defined (it is a point where it is mandatory to passed to acces goals
*       -Heuristique will pushed box to pivot point
*       -When the box reach the pivot point, a macro will autmaticly drag it to the ideal goal
*/
class HeuristiquePivot :public AHeuristique
{
    /** \brief used for the factory design pattern
     */
    friend class FHeuristique;

public:


    /** \class GameStatistique
    * \brief Represent the calculated stat and informations about the Game
    * only the information which are true during ALL the game are in this class
    */
    class GameStatistique
    {
    public:

        /** \brief Constructor of GameStatistique
         *
         * \param mapFrequentationSquares: frequentation map of the maze
         * \param pivotPoint: position of the pivot point
         * \param distMapFromPivotPoint: dist map from the pivot point (for each square, the distance to go to the pivot point)
         * \param tunnelMap: a map which identified tunnel in the maze
         *
         */
        GameStatistique(MazeMap<short> mapFrequentationSquares, short pivotPointPos, MazeMap<short> distMapFromPivotPoint, std::unordered_map<short, short> tunnelMap) :
            mapFrequentationSquares(mapFrequentationSquares), pivotPointPos(pivotPointPos), distMapFromPivotPoint(distMapFromPivotPoint), tunnelMap(tunnelMap) {};

        /** \brief Getter of the pivot Point position
         *
         * \return pivotPointPos
         *
         */
        short getPivotPointPos() const
        {
            return pivotPointPos;
        };


        /** \brief Getter of the frequentation map of the game
         *
         * \return mapFrequentationSquares
         *
         */
        MazeMap<short> getMapFrequentationSquares() const
        {
            return mapFrequentationSquares;
        };

        /** \brief return the distance to the pivot point for a specific square
         *
         * \param pos: square from which we want to have the distance
         * \return the distance
         *
         */
        short getDistFromPivotPoint(short pos) const
        {
            return distMapFromPivotPoint[pos];
        };

        /** \brief Getter of the tunnel map
         *
         * \return the tunnel map
         *
         */
        std::unordered_map<short, short> getTunnelMap() const
        {
            return tunnelMap;
        }
    private:
        /**
        * a vector of the side of the field wich is calculate like that:
        *	we make a bfs for fin the way beetween each box and the goal
        *	for each square we count how many time a box passed on it
        *	we put this info in this vector
        *
        * will not change during the game
        */
        const MazeMap<short> mapFrequentationSquares;

        /**
        * the pivotPoint is a square of the field where the passage is necessary for reach any goals
        * will never change during the game
        */
        const short pivotPointPos;

        /**
        * the dist map from the pivotPoint
        */
        const MazeMap<short> distMapFromPivotPoint;

        /**
        * map of the tunnel in the Game:
        * entrySquare => endSquare of the tunnel
        */
        const std::unordered_map<short, short> tunnelMap;
    };

public:

    /** \brief Destructor of the class HeuristiquePivot
     */
    ~HeuristiquePivot();

    /** \brief Calculate the note for a specific node
     *
     *  will automaticly set the note in the node
     * \param node: node to calculate the note
     * \param boxPushedID: box which have been pushed during the move
     * \param newPos: new position of the box
     *
     */
    virtual void calcHeuristiqueNote(Node *node, short boxPushedID, short newPos);

    /** \brief Return the name of the class
     *
     * \return the name of the class
     *
     */
    virtual std::string sayHello()
    {
        return "Pivot Method Heuristique";
    };

    /** \brief Return the first chapters of this heuristique
     *
     *  Chaptes are linked one to another
     * \return chapters
     *
     */
    Chapter* getChapters()
    {
        return &chapters;
    };


    /** \brief Will make the macro move if needed
     *
     * \param caseTracker: the list of already encoutnered Node (only there NodeRetrackInfo)
     * \param node: the current node
     * \param boxID: id of the box which have been pushed
     * \return {player_pos, box pos}	after macro moves
     *
     */
    std::pair<short, short> macroMove(std::vector<Node::NodeRetrackInfo>&caseTracker, Node *node, short boxID);

private:


    /** \brief Constructor of the class HeuristiquePivot
     *
     * \param m: maze
     * \param coefA: coef for notation of node
     * \param coefB: coef for notation of node
     * \param gameStatistique: GameStatistique of the Maze
     */
    HeuristiquePivot(Maze *m, int coefA, int coefB, GameStatistique gameStatistique);

    /** \brief Calculates chapters of the game
     *
     * \return return the first chapter of the list
     *
     */
    Chapter  calcChapter();

    /** \brief Calculate the note of the current node
     *
     * with the distance beetween each box and the pivot point
     * \return unsigned short
     *
     */
    unsigned short calc_note_distance_box_pivot();

private:

    int nb_caisse_place_best;/**< Highest number of box which have been placed on a goal during this level */

    /**
    * stats about the game
    */
    const GameStatistique gameStatistique;

    /*
    * lionked list of chapterts order by number:
    *	chapters[0]=> chapter0
    *	chapters[1]=> chapter1
    *	chapters[2]=> chapter2
    */
    Chapter  chapters;/**< Firsy chapter of the list */
};


#endif // HEURISTIQUE_H
