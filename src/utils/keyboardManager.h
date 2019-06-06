/**
 * \file keyboardManager.h
 * \brief declaration of the class keyboardManager
 * \author romain michau
 * \version 2.1
 */

#ifndef MARIOSOKOBAN_KEYBOARDMANAGER_H
#define MARIOSOKOBAN_KEYBOARDMANAGER_H


class KeyboardManager
{

public:
    KeyboardManager();

    int vitesse;


    bool keyPressed();

    char keyRead();

private:
    int lastKey;

};


#endif //MARIOSOKOBAN_KEYBOARDMANAGER_H
