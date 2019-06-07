/**
 * \file maze.h
 * \brief declaration of the class maze
 * \version 2.1
 */
#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unordered_set>
#include <queue>
#include <stack>

#include "src/Maze/GameState.h"
/**
 * Max size of the field
 */
#define NB_MAX_WIDTH     30
#define NB_MAX_HEIGHT    30


/** \enum represent all the possible type of square
 *
 */
enum
{
    SPRITE_GROUND = 0, SPRITE_WALL = 1, SPRITE_BOX = 2,
    SPRITE_BOX_PLACED = 3, SPRITE_GOAL = 4, SPRITE_MARIO = 5,
    SPRITE_DEADSQUARE = 9
};

/**
 * Represent the maze itself(labyrinthe)
 */
class Maze
{

private:
    /**
     * \brief Number of line of the maze
     */
    unsigned short m_lig;

    /**
     * \brief Number of col of the maze
     */
    unsigned short m_col;

    /**
     * \brief Position of the player
     */
    unsigned short m_pos_player;

    /**
     * \brief Path of the file representing the level
     */
    std::string m_level_path;

    /**
     * \brief Original field (before any movement is made)
     *
     * Is used for reinit the game
     */
    std::vector<unsigned char> m_field_or;

    /**
     * \brief original Position of the player
     *
     * is used for reinit the game
     */
    unsigned short m_pos_player_or;

    /**
     * \brief field itself
     */
    std::vector<unsigned char> m_field; // field

    /**
     * \brief Posisitons of all the boxes
     *
     * THE ORDER OF THE BOXES IN THE VECTOR MUST NOT ME CHANGED
     */
    std::vector<unsigned short> m_pos_boxes;

    /**
     * \brief Positions of goals
     */
    std::vector<unsigned short> m_pos_goals;

    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    /**
    * friend to the operatior << (used for display the maze)
     */
    friend std::ostream &operator<<(std::ostream &O, const Maze &n);

public:
        std::vector<char> allDirection;/**< List of all 4 directions (TOP,BOTTOM,RIGHT,LEFT) */

    /**
    * \brief Constructor of the class Maze
    * \param path: path of the file to load
    */
    Maze(const std::string &path);

    /** \brief destructor of the class Maze
     *
     */
    ~Maze();

    /**
     * \brief load the content of the file sent in paramters
     * \param path: file to load
     * \return true if the file has been succesfully load
     */
    bool _load(const std::string &path);

    /**
    * \brief Draw the field in the current state
    */
    void initDraw();

    /**
    *\brief Update the draw of the field after a mov
    *
    * init draw must have been call first
    * \param direcrion: direction of the move
    */
    void updateDraw(char direction);

    /**
     * \brief Draw a list of moves on the console
     *
     * Draw the maze on the console
     */
    void drawMove(std::vector<unsigned char> chemin, double temp, int noeudVisite);

    /** \brief Getter of gameState
     *
     * \return the current gameState of the game
     *
     */
    GameState getGameState()
    {
        return GameState(m_field, m_pos_player, m_pos_boxes);
    };


    /**
    * \brief return offset caused by the move
    *
    * top: -col
    * down: +col
    * right +1
    * left -1
    */
    short getMoveOffset(unsigned char dir) const;

    /**
    * \brief return a vector of possible adjacents position.
    *
    * \return
    * for TOP will return (LEFT, RIGHT)
    * for RIGHT will return (BOTTOM,TOP)
    * for LEFT will return (BOTTOM,TOP)
    */
    std::vector<char> getAdjacentDirection(char dir);

    /**
    * \brief return position of adjacaent walkable square
    * \return pos of the adjacent walkable squares
    */
    std::vector<short> getAdjacentWalkableSquare(short square);

    /**
    * \brief return the oppsoite direction of the one send in paramter
    * \return TOP => BOTTOM, LEFT=>RIGHT, BOTTOM=>TOP....
    */
    inline  char getOppositeDirection(char dir);

    /**
     *
     * \return true if the game is currently won
     */
    bool _isCompleted() const;

    /**
     * \brief Reinit the maze (do not work very well)
     */
    void reinit();

    /**
     * \brief Move the box in the asked direction
     * \param posBox: position of the box to move
     * \param dir: direction to push the box
     */
    void move_box(int posBox, char dir);

    /**
     * \brief Display the path one the console
     * \param vec
     */
    void lire_chemin(std::vector<unsigned char> vec);

    /**
    * \brief return all the dir doable from the square sent in parameters.
    *
    * ignore boxes
    */
    std::vector<char> getPossibleDirFromSquareIBox(short square);


    /**
    * \brief return all the dir doable from the square sent in parameters.
    *
    * dont ignore boxes
    */
    std::vector<char> getPossibleDirFromSquareWBox(short square);


    /** \brief return true if the box can be pushed in the wanted direction
     *
     * \param posBox posof the box we want to pushed
     * \param dir direction where we wants to push the pox
     * \param newPosBox unsigned short&
     * \return true if the box can be pushed
     *
     */
    bool _canPushBox(unsigned short posBox, char dir, unsigned short &newPosBox) const;

    /**
    * \brief Init the maze class
    *
    * Charge le fichier du niveau
    * \return true si le fichier c'est bien chargé
     */
    bool init();

    /**
     * Convert a field of short in a field of char
     * \param toConvert: vector to convert
     * \return converted vector
     */
    std::vector<unsigned char> convert(std::vector<unsigned short> toConvert);

    /**
     * \brief Move the player in the asked direction
     * \param dir: dir where wze wants to move the player
     * \return true if the player has been effectively move
     */
    bool updatePlayer(char dir);

    /**
     * \brief Change the state of the game
     *\param newField: new field of the game
     * \param newPosPlayer: new position of the player
     */
    void change_etat_jeu(std::vector<unsigned char> newField, unsigned short newPosPlayer);

    /**
     * \brief Change the state of the game
     * \param GameState: new GameState
     */
    void change_etat_jeu(GameState);


    /**
     *
     * \param pos
     * \return true if pos is a walkable square
     */
    bool isSquareWalkable(unsigned short pos) const;
    /**
     *
     * \param pos
     * \return true if pos is a walkable square
     */
    /**
     *
     * \param pos
     * \return true if pos is a ground square
     */
    bool isSquareGround(unsigned short pos) const;

    /**
     * True if pos is a box
     * \param pos
     * \return
     */
    bool isSquareBox(unsigned short pos) const;

    /**
     *
     * \param pos
     * \return  true if pos is a goal
     */
    bool isSquareGoal(unsigned short pos) const;

    /**
     *
     * \param pos position of the field
     * \return true if pos is a square wall
     */
    bool isSquareWall(unsigned short pos) const;

    /**
     * true if pos is th eposition of a placed box
     * \param pos
     * \return
     */
    bool isSquareBoxPlaced(unsigned short pos) const;

    /**
     * true if pos is a position of deadsquare
     * \param pos
     * \return
     */
    bool isSquareDeadSquare(unsigned short pos) const;

    /**
     * true if pos is a position of Non placed box
     * \param pos
     * \return
     */
    bool isSquareBoxNonPlaced(unsigned short pos) const;

    /**
     *
     * \return  the position of the player
     */
    unsigned short getPosPlayer() const;

    /**
     *
     * \return the size of the field (number of square)
     */
    unsigned int getSize() const;

    /**
     *
     * \return number of col
     */
    unsigned int getCol() const
    {
        return m_col;
    }

    /**
     *
     * \return  number of lig
     */
    unsigned int getLig()
    {
        return m_lig;
    }

    /**
     *
     * \return the position of boxes
     */
    std::vector<unsigned short> getPosBoxes();

    /**
     * Set a square
     * \param pos position of the square
     * \param s net type of the square
     */
    void setSquare(unsigned short pos, unsigned char s);

    /**
     * return the field
     */
    const std::vector<unsigned char> &getField() const;

    /**
     *
     * \return goalsPosition (reference)
     */
    const std::vector<unsigned short> &getGoals() const;

    /**
     *
     * \return boxes Position
     */
    std::vector<unsigned short> getPosBoxes() const;

    /**
     * Set original field
     * \param vec
     */
    void setFieldOr(std::vector<unsigned char> vec);

    /**
     * Set original pos player
     * \param newPlayerPosition
     */
    void setPlayerPosOr(unsigned short newPlayerPosition);

    /**
     * Set boxes position
     * \param newPlayerPosOr
     */
    void setPosBoxes(std::vector<unsigned short> newPlayerPosBoxes);

    /**
    * Set boxes position
    * \param newPlayerPosOr
    */
    void setPosBoxes(std::unordered_set<unsigned short> newPosBoxes);


    void setPosBox(short i, short pos);

    /**
     * Set field
     * \param newField
     */
    void setField(std::vector<unsigned char> newField);

    /**
     * Set player position
     * \param newPlayerPos
     */
    void setPlayerPos(unsigned short newPlayerPos);
};


/**
 * Set the position of the player
 * \param newPlayerPos
 */
inline void Maze::setPlayerPos(unsigned short newPlayerPos)
{
    if (newPlayerPos < this->getSize()) // NB: newPlayerPos always > 0 because unsigned short
        this->m_pos_player = newPlayerPos;
}


/**
 *
 * \return positions of goals
 */
inline const std::vector<unsigned short> &Maze::getGoals() const
{
    return this->m_pos_goals;
}

/**
 *
 * \return the field
 */
inline const std::vector<unsigned char> &Maze::getField() const
{
    return this->m_field;
}

/**
 *
 * \return size of the maze
 */
inline  unsigned int Maze::getSize() const
{
    return (int)this->m_field.size();
}

/**
 * return pos of all boxes
 */
inline std::vector<unsigned short> Maze::getPosBoxes() const
{
    return m_pos_boxes;
}

/**
 *
 * \return pos of the player
 */
inline unsigned short Maze::getPosPlayer() const
{
    return m_pos_player;
}

inline void Maze::setSquare(unsigned short pos, unsigned char s)
{
    if (pos < (this->m_lig * this->m_col))
    {
        this->m_field[pos] = s;
    }
}


/**
 *
 * \param pos
 * \return true if pos is a walkable square (deadsquare, goal or ground)
 */
inline bool Maze::isSquareWalkable(unsigned short pos) const
{
    if (pos < 0 || pos >= getSize())
    {
        return false;
    }
    return ((this->m_field[pos] == SPRITE_GROUND || this->m_field[pos] == SPRITE_GOAL ||
             this->m_field[pos] == SPRITE_DEADSQUARE) ? true : false);
}

inline bool Maze::isSquareGround(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_GROUND) ? true : false);
}

/**
* \return true is pos is a box (placed or not)
*/
inline bool Maze::isSquareBox(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_BOX || this->m_field[pos] == SPRITE_BOX_PLACED) ? true : false);
}

inline bool Maze::isSquareBoxNonPlaced(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_BOX) ? true : false);
}

inline bool Maze::isSquareGoal(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_GOAL ? true : false);
}

inline bool Maze::isSquareWall(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_WALL ? true : false);
}

inline bool Maze::isSquareBoxPlaced(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_BOX_PLACED ? true : false);
}

inline bool Maze::isSquareDeadSquare(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_DEADSQUARE ? true : false);
}


#endif // MAZE_H_INCLUDED
