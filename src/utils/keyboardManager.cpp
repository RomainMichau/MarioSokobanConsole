/**
 * \file keyboardManager.cpp
 * \brief implementation of the class keyboardManager
 * \author Romain Michau
 * \version 2.1
 */
#include "src/utils/KeyboardManager.h"
#include <conio.h>
#include <iostream>

using namespace std;
KeyboardManager::KeyboardManager()   {}


bool KeyboardManager::keyPressed()
{
    if(kbhit())
    {
        //    cout<<"key press"<<std::endl;
        lastKey=_getch();
        //  cout<<lastKey<<"getch";
        return true;
    }
    return false;
}

char KeyboardManager::keyRead()
{
    return lastKey;
}
