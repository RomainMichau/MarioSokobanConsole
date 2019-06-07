#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED
/**
 * \file Console.h
 * \brief declaration of the class console
 * \version 2.1
 */


#include <iostream>

/** \enum list of possible color for the console
 */

enum Color
{
    _COLOR_BLACK = 0,
    _COLOR_WHITE = 1,
    _COLOR_RED = 2,
    _COLOR_GREEN = 3,
    _COLOR_BLUE = 4,
    _COLOR_YELLOW = 5,
    _COLOR_PURPLE = 6,
    _COLOR_DEFAULT = 7, // gris couleur de base de la console
};

/** \class  Console
 * \brief used for display things on the console
 */

class Console
{
private:
    /** \brief constructor of the class Console
     *
     */
    Console();

     /** \brief destructor of the class Console
     *
     */
    ~Console();

    static Console* m_instance;


    void _setColor(short unsigned int front, short unsigned int back);
public:

    static Console* getInstance();

    static void deleteInstance();

    void gotoLigCol(short int lig, short int col);

    void gotoCurrentLigCol(short int lig, short int col);

    void gotoCol(short int col);

    bool isKeyboardPressed();

    int getInputKey();

    void setColor(int col);
};

#endif // CONSOLE_H_INCLUDED
