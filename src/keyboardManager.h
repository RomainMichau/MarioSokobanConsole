//
// Created by rmichau on 26/04/2019.
//

#ifndef MARIOSOKOBAN_KEYBOARDMANAGER_H
#define MARIOSOKOBAN_KEYBOARDMANAGER_H


class keyboardManager {

public:
    keyboardManager();

    int vitesse;

    bool init();

    bool keyPressed();

    char keyRead();

private:
    int lastKey;

};


#endif //MARIOSOKOBAN_KEYBOARDMANAGER_H
