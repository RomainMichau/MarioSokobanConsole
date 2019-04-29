/************************************************************
Sokoban project - Maze file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
#include <stack>
/**
 * Max size of the field
 */
#define NB_MAX_WIDTH     30
#define NB_MAX_HEIGHT    30



enum {
	SPRITE_GROUND = 0, SPRITE_WALL = 1, SPRITE_BOX = 2,
	SPRITE_BOX_PLACED = 3, SPRITE_GOAL = 4, SPRITE_MARIO = 5,
	SPRITE_DEADSQUARE = 9
};

/**
 * Represent the maze (labyrinthe)
 */
class Maze {
public:
	/**
	* Constructor
	* @param path path of the file to load
	*/
	Maze(const std::string &path);

	/**
	 * destructor
	 */
	~Maze();

private:
	/**
	 * Number of line of the maze
	 */
	unsigned short m_lig;

	/**
	 * Number of col of the maze
	 */
	unsigned short m_col;

	/**
	 * Position of the player
	 */
	unsigned short m_pos_player;
	char m_dir_player;

	/**
	 * Path of the file representing the level
	 */
	std::string m_level_path;

	/**
	 * Original field (before any movement is made)
	 * Is used for reinit the game
	 */
	std::vector<unsigned char> m_field_or;

	/**
	 * original Position of the player
	 * is used for reinit the game
	 */
	unsigned short m_pos_player_or;

	/**
	 * field
	 */
	std::vector<unsigned char> m_field; // field

	/**
	 * Posisitons of all the boxex
	 */
	std::vector<unsigned short> m_pos_boxes;

	/**
	 * Positions of goals
	 */
	std::vector<unsigned short> m_pos_goals;




	/**
	 * Surcharge de l'operateur (je sais pas trop comment ça marche)
	 * @param O
	 * @param n
	 * @return
	 */
	friend std::ostream &operator<<(std::ostream &O, const Maze &n);


	/**
	 * Charge le fichier dont le chemin est envoyé en parametre
	 * @param path
	 * @return
	 */
	bool _load(const std::string &path);

	/**
	* Draw the field in the current state
	*/
	void initDraw();

	/**
	* Update the draw of the field after a mov
	* init draw must have been call first
	* @param direcrion: direction of the move
	*/
	void updateDraw(char direction);


public:

	/**
	* return offset caused by the move
	* top: -col
	* down: +col
	* right +1
	* left -1
	*/
	short getMoveOffset(unsigned char dir);

	/**
	* return a vector of possible adjacents position.
	* example:
	* for top will return (left, right)
	* for right will return (bootom,tom)
	* for left will return (bottom,top)
	*/
	std::vector<char> getAdjacentDirection(char dir);

	/**
	List des 4 directions
	*/
	std::vector<char> allDirection;

	/**
	 * True if deadlocks are actives
	 */
	bool case_morte_activ;

	/**
	 *
	 * @return true if the game is currently won
	 */
	bool _isCompleted() const;

	/**
	 * Reinit the maze
	 */
	void reinit();

	/**
	 * Move the box in the asked direction
	 * @param posBox
	 * @param dir
	 */
	void move_box(int posBox, char dir);

	/**
	 * Draw the maze on the console
	 */
	void drawMove(std::vector<unsigned char> chemin, double temp, int noeudVisite);


	/**
	 * Display the path one the console
	 * @param vec
	 */
	void lire_chemin(std::vector<unsigned char> vec);




	bool _canPushBox(unsigned short posBox, char dir, unsigned short &newPosBox) const;

	int cpt;

	/**
	* Initialise la classe Maze.
	* Charge le fichier du niveau
	* @return true si le fichier c'est bien chargé
	 */
	bool init();

	/**
	 * Convert a field of short in a field of char
	 * @param toConvert
	 * @return
	 */
	std::vector<unsigned char> convert(std::vector<unsigned short> toConvert);

	/**
	 * Move the player in the asked direction
	 * @param dir
	 * @return
	 */
	bool updatePlayer(char dir);

	/**
	 * Change the state of the game
	 */
	void change_etat_jeu(std::vector<unsigned char>, unsigned short);

	/**
	 * Change the state of the game
	 * @param vec
	 * @param a
	 */
	void change_etat_jeu(std::vector<unsigned char> field, std::vector<bool> accesible_zone);

	/**
	 *
	 * @param pos
	 * @return true if pos is a walkable square
	 */
	bool isSquareWalkable(unsigned short pos) const;

	bool isSquareGround(unsigned short pos) const;

	/**
	 * True if pos is a box
	 * @param pos
	 * @return
	 */
	bool isSquareBox(unsigned short pos) const;

	/**
	 *
	 * @param pos
	 * @return  true if pos is a goal
	 */
	bool isSquareGoal(unsigned short pos) const;

	/**
	 *
	 * @param pos position of the field
	 * @return true if pos is a square wall
	 */
	bool isSquareWall(unsigned short pos) const;

	/**
	 * true if pos is th eposition of a placed box
	 * @param pos
	 * @return
	 */
	bool isSquareBoxPlaced(unsigned short pos) const;

	/**
	 * true if poos is a position of deadsquare
	 * @param pos
	 * @return
	 */
	bool isSquareDeadSquare(unsigned short pos) const;


	bool isSquareBoxNonPlaced(unsigned short pos) const;

	// Other getters
	const std::string &getLevelPath() const;

	/**
	 *
	 * @return  the position of the player
	 */
	unsigned short getPosPlayer() const;

	/**
	 *
	 * @return the size of the field (number of square)
	 */
	 int getSize() const;

	/**
	 *
	 * @return number of col
	 */
	unsigned int getCol() { return m_col; }

	/**
	 *
	 * @return  number of lig
	 */
	unsigned int getLig() { return m_lig; }

	/**
	 *
	 * @return the position of boxes
	 */
	std::vector<unsigned short> getPosBoxes();

	/**
	 * Set a square
	 * @param pos position of the square
	 * @param s net type of the square
	 */
	void setSquare(unsigned short pos, unsigned char s);

	/**
	 * return the field
	 */
	const std::vector<unsigned char> &getField() const;

	/**
	 *
	 * @return goalsPosition (reference)
	 */
	const std::vector<unsigned short> &getGoals() const;

	/**
	 *
	 * @return boxes Position
	 */
	std::vector<unsigned short> getPosBoxes() const;

	/**
	 * Set original field
	 * @param vec
	 */
	void setFieldOr(std::vector<unsigned char> vec);

	/**
	 * Set original pos player
	 * @param newPlayerPosition
	 */
	void setPlayerPosOr(unsigned short newPlayerPosition);

	/**
	 * Set boxes position
	 * @param newPlayerPosOr
	 */
	void setPosBoxes(std::vector<unsigned short> newPlayerPosOr);

	/**
	 * Set field
	 * @param newField
	 */
	void setField(std::vector<unsigned char> newField);

	/**
	 * Set player position
	 * @param newPlayerPos
	 */
	void setPlayerPos(unsigned short newPlayerPos);
};


/**
 * Set the position of the player
 * @param newPlayerPos
 */
inline void Maze::setPlayerPos(unsigned short newPlayerPos) {
	if (newPlayerPos < this->getSize()) // NB: newPlayerPos always > 0 because unsigned short
		this->m_pos_player = newPlayerPos;
}


/**
 *
 * @return positions of goals
 */
inline const std::vector<unsigned short> &Maze::getGoals() const { return this->m_pos_goals; }

/**
 *
 * @return the field
 */
inline const std::vector<unsigned char> &Maze::getField() const { return this->m_field; }

/**
 *
 * @return size of the maze
 */
inline  int Maze::getSize() const { return this->m_field.size(); }

/**
 * return pos of all boxes
 */
inline std::vector<unsigned short> Maze::getPosBoxes() const { return m_pos_boxes; }

/**
 *
 * @return pos of the player
 */
inline unsigned short Maze::getPosPlayer() const { return m_pos_player; }

inline void Maze::setSquare(unsigned short pos, unsigned char s) {
	if (pos < (this->m_lig * this->m_col)) {
		this->m_field[pos] = s;
	}
}

inline bool Maze::isSquareWalkable(unsigned short pos) const {
	return ((this->m_field[pos] == SPRITE_GROUND || this->m_field[pos] == SPRITE_GOAL ||
		this->m_field[pos] == SPRITE_DEADSQUARE) ? true : false);
}

inline bool Maze::isSquareGround(unsigned short pos) const {
	return ((this->m_field[pos] == SPRITE_GROUND) ? true : false);
}

/**
* @return true is pos is a box (placed or not)
*/
inline bool Maze::isSquareBox(unsigned short pos) const {
	return ((this->m_field[pos] == SPRITE_BOX || this->m_field[pos] == SPRITE_BOX_PLACED) ? true : false);
}

inline bool Maze::isSquareBoxNonPlaced(unsigned short pos) const {
	return ((this->m_field[pos] == SPRITE_BOX) ? true : false);
}

inline bool Maze::isSquareGoal(unsigned short pos) const {
	return (this->m_field[pos] == SPRITE_GOAL ? true : false);
}

inline bool Maze::isSquareWall(unsigned short pos) const {
	return (this->m_field[pos] == SPRITE_WALL ? true : false);
}

inline bool Maze::isSquareBoxPlaced(unsigned short pos) const {
	return (this->m_field[pos] == SPRITE_BOX_PLACED ? true : false);
}

inline bool Maze::isSquareDeadSquare(unsigned short pos) const {
	return (this->m_field[pos] == SPRITE_DEADSQUARE ? true : false);
}


#endif // MAZE_H_INCLUDED
