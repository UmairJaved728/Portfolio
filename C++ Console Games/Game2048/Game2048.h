#ifndef PROJECT_2048_GAME__GAME2048_H
#define PROJECT_2048_GAME__GAME2048_H

#include<iostream>

using namespace std;

// Grid size
#define ROWS 4
#define COLS 4

class Tile{
public:
    int value;
    bool isMine;
    bool isCombined;

    Tile(){
        value = 0;
        isMine = false;
        isCombined = false;
    }
};

class Game2048{
protected:
    int points;
    Tile grid[ROWS][COLS];

    void initBoard();
    void resetBoard();
    void placeNewTile(int r, int c);
    void getRandomEmptyCell(int &r, int &c);
    void printBoard();
    void readyBoard();
    int moveUp();
    int moveDown();
    int moveLeft();
    int moveRight();
    bool isWin();
    bool isGameOver();

public:
    Game2048();
};


#endif //PROJECT_2048_GAME__GAME2048_H
