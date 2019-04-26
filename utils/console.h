#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <iostream>

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

class Console
{
    private:
        // Empecher la création
        Console();

        ~Console();

        // Empecher la copie d'objet...
        Console& operator= (const Console&){ return *this;}
        Console (const Console&){}

        // Attributs
        static Console* m_instance;

        // Méthodes privées
        void _setColor(short unsigned int front, short unsigned int back);
    public:
        // Méthodes statiques (publiques)
        static Console* getInstance();

        static void deleteInstance();

        // Méthodes publiques
        void gotoLigCol(short int lig, short int col);

        void gotoCurrentLigCol(short int lig, short int col);

        void gotoCol(short int col);

        bool isKeyboardPressed();

        int getInputKey();

        void setColor(int col);
};

#endif // CONSOLE_H_INCLUDED
