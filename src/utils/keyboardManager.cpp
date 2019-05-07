//
// Created by rmichau on 26/04/2019.
//

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
