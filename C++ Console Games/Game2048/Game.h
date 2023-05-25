
#ifndef PROJECT_2048_GAME__GAME_H
#define PROJECT_2048_GAME__GAME_H

#include<iostream>
#include "HallOfFame.h"
#include "Game2048.h"

using namespace std;

class Game: public Game2048{
    HallOfFame hall;

    bool confirm()
    {
        char ch;
        do {
            cout << "\nAre you sure? [y/n]: ";
            cin >> ch;
            ch |= 32;
            if(ch != 'y' && ch != 'n')
                cout << "\nInvalid Input! Try Again...\n";
        }while(ch != 'y' && ch != 'n');

        if(ch == 'y')
            return true;
        return false;
    }
public:
    Game();
    static void printRules();
    static void printControls();
    void play();
    void saveGame();
    void loadGame();
    static char promptInput();
};

#endif //PROJECT_2048_GAME__GAME_H
