/**
 * \file maze.cpp
 * \brief implementation of the class maze
 * \version 2.1
 */
#include "src/Maze/Maze.h"
#include "src/utils/KeyboardManager.h"
#include "src/utils/Console.h"
#include "src/utils/Coord.h"
#include <fstream>
#include <queue>
#include <Windows.h>
#include <stack>
#include <iomanip>

/**
 * Constructeur du Maze.
 * @param path chemin du niveau à charger
 */
Maze::Maze(const std::string& path)
    : m_lig(0), m_col(0), m_pos_player(0),  m_level_path(path)
{
    allDirection.push_back(TOP);
    allDirection.push_back(BOTTOM);
    allDirection.push_back(LEFT);
    allDirection.push_back(RIGHT);

}

Maze::~Maze()
{
}


/**
 * Init the game
 * @return
 */
bool Maze::init()
{
    bool res = this->_load(this->m_level_path);
    if (!res)
    {
        std::cerr << "Cannot load maze... Check file : " << this->m_level_path << std::endl;
        system("pause");

        return false;
    }

    return res;
}

/**
 * Set the field
 * @param newField
 */
void Maze::setField(std::vector<unsigned char> newField)
{
    m_field = newField;

}

/**
 * Reinit the maze (don't wprk i think)
 */
void Maze::reinit()
{
    change_etat_jeu(m_field_or, m_pos_player_or);
}

/**
 * Set origin field state
 * @param vec
 */
void Maze::setFieldOr(std::vector<unsigned char> vec)
{
    m_field_or = vec;
}

/**
 * The the position of the player
 * @param newPlayerPosition
 */
void Maze::setPlayerPosOr(unsigned short newPlayerPosition)
{
    m_pos_player_or = newPlayerPosition;
}

/**
 * Get the position of the box
 * @return
 */
std::vector<unsigned short> Maze::getPosBoxes()
{
    return(m_pos_boxes);
}

/**
 * Set the new positions of the box
 * @param newPlayerPosOr
 */
void Maze::setPosBoxes(std::vector<unsigned short> newBoxPoses)
{

    for (unsigned short box : m_pos_boxes)
    {
        this->m_field[box] = SPRITE_GROUND;
    }
    for (unsigned short box : newBoxPoses)
    {
        this->m_field[box] = SPRITE_BOX;
    }
    m_pos_boxes = newBoxPoses;
}

/**
 * Set the new positions of the box
 * @param newPlayerPosOr
 */
void Maze::setPosBoxes(std::unordered_set<unsigned short> newBoxPoses)
{

    for (unsigned short box : m_pos_boxes)
    {
        this->m_field[box] = SPRITE_GROUND;
    }
    for (unsigned short box : newBoxPoses)
    {
        this->m_field[box] = SPRITE_BOX;
    }
    m_pos_boxes = std::vector<unsigned short>(newBoxPoses.begin(),newBoxPoses.end());
}

void Maze::setPosBox(short i, short pos)
{
    m_pos_boxes[i] = pos;

    short a = 0;
    for (unsigned short s : getPosBoxes())
        if (s == 76 || s == 90 || s == 103 || s == 104 || s == 105 || s == 106)
            a++;
    if (a == 6)
        std::cout << this;
}

/**
 *
 * @return true if the game is currently won
 */
bool Maze::_isCompleted() const
{
    for (unsigned int i = 0; i < this->m_pos_boxes.size(); ++i)
    {
        if (!this->isSquareBoxPlaced(this->m_pos_boxes[i]))
            return false;
    }
    return true;
}

/*
*/
std::vector<char> Maze::getPossibleDirFromSquareIBox(short square)
{
    std::vector<char> possibleDir;
    for (char dir : allDirection)
    {
        short newSquare = square + getMoveOffset(dir);
        if (newSquare > 0 && newSquare < getSize() && (isSquareWalkable(newSquare) || isSquareBox(newSquare)))
            possibleDir.push_back(dir);
    }
    return possibleDir;
}


std::vector<char> Maze::getPossibleDirFromSquareWBox(short square)
{
    std::vector<char> possibleDir;
    for (char dir : allDirection)
    {
        short newSquare = square + getMoveOffset(dir);
        if (newSquare > 0 && newSquare < getSize() && (isSquareWalkable(newSquare)))
            possibleDir.push_back(dir);
    }
    return possibleDir;
}

/**
 * Return true if the box can be pushed in the direction send in parameter.
 * wont take in count the deadlocks
 * @param posBox
 * @param dir
 * @param newPosBox new position of the box
 * @return true if the box can be pushed
 */
bool Maze::_canPushBox(unsigned short posBox, char dir, unsigned short& newPosBox) const
{
    // Check if this position is a box !
    if (!this->isSquareBox(posBox))
        return false;

    // Compute new position according to push direction
    newPosBox = Coord::getDirPos(posBox, dir);

    // Can we push the box ?
    return this->isSquareWalkable(newPosBox);
}

/**
 * Charge le fichier dont le chemin est envoyé en parametre
 * @param path
 * @return
 */
bool Maze::_load(const std::string& path)
{
    std::vector<unsigned short> tmpPosBoxes;
    std::ifstream ifs(path.c_str());
    if (ifs)
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(ifs, line))
        {
            lines.push_back(line);
            this->m_lig++;
            this->m_col = (this->m_col < line.size() ? line.size() : this->m_col);
        }
        ifs.close();

        if (this->m_col > NB_MAX_WIDTH || this->m_lig > NB_MAX_HEIGHT)
        {
            std::cerr << "Maze::load => Bad formatting in level data..." << std::endl;
            return false;
        }

        Coord::m_nb_col = this->m_col;
        for (unsigned int i = 0; i < lines.size(); i++)
        {
            //LDebug << "Maze::load => Reading : " << lines[i];
            for (unsigned int j = 0; j < this->m_col; j++)
            {
                if (j < lines[i].size())
                {
                    bool both = false;
                    unsigned short pos = Coord::coord1D(i, j);
                    unsigned char s = (unsigned char)(lines[i][j] - '0');

                    // Need to add a goal and a box ;)
                    if (s == SPRITE_BOX_PLACED)
                    {
                        both = true;
                    }

                    if (s == SPRITE_GOAL || both)
                    {
                        this->m_pos_goals.push_back(pos);
                    }
                    if (s == SPRITE_BOX || both)
                    {
                        tmpPosBoxes.push_back(pos);
                    }

                    // Assign player position
                    if (s == SPRITE_MARIO)
                    {
                        this->m_pos_player = pos;
                        //LDebug << "\tAdding player pos (" << pos << ")";
                        s = SPRITE_GROUND;
                    }

                    // Add this value in the field
                    this->m_field.push_back(s);
                }
                else
                {
                    // Here - Out of bound
                    this->m_field.push_back(SPRITE_GROUND);
                }
            }
        }

        // Copy box position
        this->m_pos_boxes.resize(tmpPosBoxes.size());
        for (unsigned int i = 0; i < tmpPosBoxes.size(); ++i)
        {
            this->m_pos_boxes[i] = tmpPosBoxes[i];
        }

        return (this->m_pos_boxes.size() == this->m_pos_goals.size());
    }
    else
    {
        std::cerr << "Maze::load => File does not exist..." << std::endl;
    }

    return false;
}



/**
 * Change la position du player en fonction de la direction envoyé en parametre
 * @param dir direction à prendre
 * @return renvoit true si le jeu est gagné apres ce mouvement
 */
bool Maze::updatePlayer(char dir)
{
    unsigned short a = 0;
    unsigned short copyPosPlayer = 0;

    if (dir < 0 || dir > MAX_DIR)
    {
        std::cerr << "Maze::updatePlayer => Direction not correct... " << +dir << std::endl;
        return false;
    }

    if (dir == TOP && !isSquareWall(m_pos_player - getCol()))   //Si le joueur va vers le haut
    {

        copyPosPlayer = m_pos_player - getCol();
        if (isSquareBox(m_pos_player - getCol()) == 1 && _canPushBox(copyPosPlayer, dir, a))            //si il y a une brique poussable
        {
            move_box(m_pos_player - getCol(), dir);
            m_pos_player -= getCol();
        }
        else if (isSquareWalkable(m_pos_player - getCol()))
            m_pos_player -= getCol();
    }

    if (dir == BOTTOM && (!isSquareWall(m_pos_player + getCol())))  //Vers le Bas
    {

        if (isSquareBox(m_pos_player + getCol()) == 1 && _canPushBox(m_pos_player + getCol(), dir, a))
        {

            move_box(m_pos_player + getCol(), dir);
            m_pos_player += getCol();
        }
        else if (isSquareWalkable(m_pos_player + getCol()))
            m_pos_player += getCol();
    }

    if (dir == RIGHT && isSquareWall(m_pos_player + 1) == 0)  //vers la droite, best destination ever #team droitier
    {

        if (isSquareBox(m_pos_player + 1) == 1 && _canPushBox(m_pos_player + 1, dir, a) == 1)
        {
            move_box(m_pos_player + 1, dir);
            m_pos_player += 1;
        }
        else if (isSquareWalkable(m_pos_player + 1))
            m_pos_player++;
    }
    if (dir == LEFT && isSquareWall(m_pos_player - 1) == 0)  //Vers la gauche, RT si t'es triste :'(
    {

        if (isSquareBox(m_pos_player - 1) == 1 && _canPushBox(m_pos_player - 1, dir, a) == 1)
        {
            move_box(m_pos_player - 1, dir);
            m_pos_player--;
        }
        else if (isSquareWalkable(m_pos_player - 1))
            m_pos_player--;
    }
    // Implement player moving and pushing here
    if (!_isCompleted())
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Display field on the console
 */
void Maze::updateDraw(char mov)
{
    Sleep(50);
    Console* c = Console::getInstance();
    bool boxPush = false;
    short offset = getMoveOffset(mov);
    short orPlayer = getPosPlayer();
    short newPosPlayer = getPosPlayer() + offset;
    short newBoxPos = getPosPlayer() + offset * 2;
    if (isSquareBox(newPosPlayer))
    {
        boxPush = true;
    }
    unsigned int lig = 0, col = 0;
    Coord::coord2D(orPlayer, lig, col);
    lig += 3;
    col *= 2;
    c->gotoLigCol(lig, col);

    if (isSquareDeadSquare(orPlayer))
    {
        c->setColor(_COLOR_RED);
        std::cout << SPRITE_DEADSQUARE;
    }
    else
    {
        c->setColor(_COLOR_WHITE);
        std::cout << SPRITE_GROUND;
    }
    Coord::coord2D(newPosPlayer, lig, col);
    lig += 3;
    col *= 2;
    c->gotoLigCol(lig, col);
    c->setColor(_COLOR_YELLOW);
    std::cout << SPRITE_MARIO;
    if (boxPush)
    {
        Coord::coord2D(newBoxPos, lig, col);
        lig += 3;
        col *= 2;
        c->gotoLigCol(lig, col);
        Console::getInstance()->setColor(_COLOR_GREEN);
        std::cout << SPRITE_BOX;
    }
    this->updatePlayer(mov);
}

/**
* return the offset created a mov in this dir
*/
short Maze::getMoveOffset(unsigned char dir) const
{
    switch (dir)
    {
    case TOP:
        return -this->getCol();
    case BOTTOM:
        return this->getCol();
    case LEFT:
        return -1;
    case RIGHT:
        return 1;
    }
    return 0;
}

std::vector<char> Maze::getAdjacentDirection(char dir)
{
    std::vector<char> adjDir;
    switch (dir)
    {
    case LEFT:
    case RIGHT:
        adjDir.push_back(TOP);
        adjDir.push_back(BOTTOM);
        break;
    case TOP:
    case BOTTOM:
        adjDir.push_back(LEFT);
        adjDir.push_back(RIGHT);
        break;
    default:
        break;
    }
    return adjDir;

}

std::vector<short> Maze::getAdjacentWalkableSquare(short square)
{
    std::vector<short> res;
    for (char dir : allDirection)
    {
        short offset = getMoveOffset(dir);
        short adjSquare = square + offset;
        if (adjSquare >= 0 && adjSquare < this->getSize() && this->isSquareWalkable(adjSquare))
            res.push_back(adjSquare);
    }
    return res;

}

inline  char Maze::getOppositeDirection(char dir)
{
    switch (dir)
    {
    case TOP:
        return BOTTOM;
    case BOTTOM:
        return TOP;
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    default:
        return 0;
    }
}

/**
* Draw the field in the current state
*/
void Maze::initDraw()
{

    for (unsigned int l = 0; l < this->getSize(); l++)
    {
        if (l == this->m_pos_player)
            Console::getInstance()->setColor(_COLOR_YELLOW);
        else if (this->isSquareWall(l))
            Console::getInstance()->setColor(_COLOR_PURPLE);
        else if (this->isSquareBoxPlaced(l) || this->isSquareGoal(l))
            Console::getInstance()->setColor(_COLOR_GREEN);
        else if (this->isSquareBox(l))
            Console::getInstance()->setColor(_COLOR_BLUE);
        else if (this->m_field[l] == SPRITE_DEADSQUARE)
            Console::getInstance()->setColor(_COLOR_RED);
        else
            Console::getInstance()->setColor(_COLOR_WHITE);

        std::cout << +this->m_field[l] << " "; // + => print as "int"

        if ((l + 1) % this->m_col == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

}

/**
* Update the draw of the field
* init draw must have been call first
*/
void Maze::drawMove(std::vector<unsigned char> chemin, double temp, int noeudVisit)
{
    system("CLS");
    Console* c = Console::getInstance();

    c->gotoLigCol(this->getLig() + 10, 0);
    std::cout << std::endl;
    std::cout << chemin.size() << " mouvements" << std::endl;
    for (short c : chemin)
    {
        std::cout << c << " ";
    }
    c->gotoLigCol(0, 0);
    std::cout << "temps: " << temp << " s" << std::endl << "noeuds visite:" << noeudVisit << std::endl << std::endl;
    this->initDraw();
    for (int i = 0; i < chemin.size(); i++)
    {
        this->updateDraw(chemin[i]);
    }
}


/**
 * Overload function for displaying debug information
 * about Maze class
 * @param O
 * @param m
 * @return
 */
std::ostream& operator << (std::ostream& O, const Maze& m)
{
    unsigned int l, c;
    int i = 0;
    Coord::coord2D(m.m_pos_player, l, c);
    O << "Player position " << m.m_pos_player << " (" << l << "," << c << ")" << std::endl;
    O << "Field Size " << +m.m_lig << " x " << +m.m_col << " = " << m.getSize() << std::endl;
    O << "Field Vector capacity : " << m.m_field.capacity() << std::endl;
    O << "Field array : " << std::endl << std::endl;
    for (unsigned int l = 0; l < m.getSize(); l++)
    {
        if (l == m.m_pos_player)
            Console::getInstance()->setColor(_COLOR_YELLOW);
        else if (m.isSquareWall(l))
            Console::getInstance()->setColor(_COLOR_PURPLE);
        else if (m.isSquareBoxPlaced(l) || m.isSquareGoal(l))
            Console::getInstance()->setColor(_COLOR_GREEN);
        else if (m.isSquareBox(l))
            Console::getInstance()->setColor(_COLOR_BLUE);
        else if (m.m_field[l] == SPRITE_DEADSQUARE)
            Console::getInstance()->setColor(_COLOR_RED);
        else
            Console::getInstance()->setColor(_COLOR_WHITE);

        O << std::setw(2) << +m.m_field[l] << " "; // + => print as "int"

        if ((l + 1) % m.m_col == 0)
        {
            O << std::endl;
        }
    }
    Console::getInstance()->setColor(_COLOR_DEFAULT);
    O << std::endl;

    return O;
}


/**
 * Move the box in the asked direction
 * @param posBox postion of the box
 * @param dir  direction to push the box
 */
void Maze::move_box(int posBox, char dir)
{

    int i = 0;
    while (m_pos_boxes[i] != posBox)
    {
        i++;

    }
    if (dir == TOP)
    {

        if (isSquareBoxPlaced(m_pos_player - getCol()))
            setSquare(m_pos_player - getCol(), 4);
        else
        {
            setSquare(m_pos_player - getCol(), 0);
        }

        if (isSquareGoal(m_pos_player - 2 * getCol()))
            setSquare(m_pos_player - 2 * getCol(), 3);
        else
        {
            setSquare(m_pos_player - 2 * getCol(), 2);
        }
        m_pos_boxes[i] -= getCol();
    }
    else  if (dir == BOTTOM)
    {
        if (isSquareBoxPlaced(m_pos_player + getCol()))
            setSquare(m_pos_player + getCol(), 4);
        else
        {
            setSquare(m_pos_player + getCol(), 0);
        }

        if (isSquareGoal(m_pos_player + 2 * getCol()))
            setSquare(m_pos_player + 2 * getCol(), 3);
        else
        {
            setSquare(m_pos_player + 2 * getCol(), 2);
        }
        m_pos_boxes[i] += getCol();
    }
    else  if (dir == LEFT)
    {
        if (isSquareBoxPlaced(m_pos_player - 1))
            setSquare(m_pos_player - 1, 4);
        else
        {
            setSquare(m_pos_player - 1, 0);
        }

        if (isSquareGoal(m_pos_player - 2))
            setSquare(m_pos_player - 2, 3);
        else
        {
            setSquare(m_pos_player - 2, 2);
        }
        m_pos_boxes[i] -= 1;
    }
    else  if (dir == RIGHT)
    {
        if (isSquareBoxPlaced(m_pos_player + 1))
            setSquare(m_pos_player + 1, 4);
        else
        {
            setSquare(m_pos_player + 1, 0);
        }

        if (isSquareGoal(m_pos_player + 2))
            setSquare(m_pos_player + 2, 3);
        else
        {
            setSquare(m_pos_player + 2, 2);
        }
        m_pos_boxes[i] += 1;
    }
    short a = 0;
    for (unsigned short s : getPosBoxes())
        if (s == 76 || s == 90 || s == 103 || s == 104 || s == 105 || s == 106)
            a++;
    if (a == 6)
        std::cout << this;
}

/**
 * Convert the field in short format to field in char format
 * @param toConvert
 * @return
 */
std::vector<unsigned char> Maze::convert(std::vector<unsigned short> toConvert)
{
    std::vector<unsigned char> reso;
    for (int i = 0; i < toConvert.size(); i++)
    {
        if (toConvert[i] == 0)
            reso.push_back(TOP);
        if (toConvert[i] == 1)
            reso.push_back(BOTTOM);
        if (toConvert[i] == 2)
            reso.push_back(LEFT);
        if (toConvert[i] == 3)
            reso.push_back(RIGHT);
    }
    return reso;


}

/**
 * Display the path on the console
 * @param vec
 */
void Maze::lire_chemin(std::vector<unsigned char> vec)
{
    std::cout << std::endl;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == TOP)
            std::cout << "TOP-";
        if (vec[i] == BOTTOM)
            std::cout << "BOTTOM-";
        if (vec[i] == LEFT)
            std::cout << "LEFT-";
        if (vec[i] == RIGHT)
            std::cout << "RIGHT-";
    }



}

/**
 * Change the state of the game (field and posPlayer)
 * @param newField
 * @param newPosPlayer
 */
void Maze::change_etat_jeu(std::vector<unsigned char> newField, unsigned short newPosPlayer)
{
    m_field = newField;
    int b = 0;
    unsigned short p = 0;
    for (int i = 0; i < newField.size(); i++)
    {
        if (m_field[i] == SPRITE_BOX || m_field[i] == SPRITE_BOX_PLACED)
        {
            m_pos_boxes[b] = i;




            b++;
        }

    }
    m_pos_player = newPosPlayer;
    short a = 0;
    for (unsigned short s : getPosBoxes())
        if (s == 76 || s == 90 || s == 103 || s == 104 || s == 105 || s == 106)
            a++;
    if (a == 6)
        std::cout << this;
}
/**
 * Change the state of the game (field and posPlayer)
 * @param newField
 * @param newPosPlayer
 */
void Maze::change_etat_jeu(GameState gameState)
{
    m_field = gameState.field;
    int b = 0;
    unsigned short p = 0;
    m_pos_boxes = gameState.posBox;
    m_pos_player = gameState.posPlayer;
    short a = 0;
    for (unsigned short s : getPosBoxes())
        if (s == 76 || s == 90 || s == 103 || s == 104 || s == 105 || s == 106)
            a++;
    if (a == 6)
        std::cout << this;
}




