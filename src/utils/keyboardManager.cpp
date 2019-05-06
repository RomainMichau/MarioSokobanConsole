//
// Created by rmichau on 26/04/2019.
//

#include "src/utils/keyboardManager.h"
#include <conio.h>
#include <iostream>

using namespace std;
keyboardManager::keyboardManager()   {}


bool keyboardManager::keyPressed()
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

char keyboardManager::keyRead()
{
    return lastKey;
}