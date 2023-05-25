#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Cell.h"

using namespace std;

class Board{
    int size;
    int rows;
    int cols;
    Cell *board;

public:
    explicit Board(int size = 100);
    void initializeBoard(int numOfSnakes, int numOfLadders);
    void setLadders(int numOfLadders);
    void setSnakes(int numOfSnakes);
    void printBoard(int *playerPositions, int *playerNumbers, int numOfPlayers);
    int getNextPosition(int currentPosition, int dice);
    void writeBoard(ostream &file);
    void readBoard(istream &file);
    ~Board();
};

#endif //PROJECT_BOARD_H
