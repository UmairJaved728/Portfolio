
#ifndef PROJECT_CELL_H
#define PROJECT_CELL_H

#include <iostream>
using namespace std;

class Cell{
public:
    int value;
    bool isSnake;
    bool isSnakeStart;
    bool isSnakeEnd;
    bool isLadder;
    bool isLadderStart;
    bool isLadderEnd;
    int number;

    Cell() {
        value = -1;
        isSnake = false;
        isSnakeStart = false;
        isSnakeEnd = false;
        isLadder = false;
        isLadderStart = false;
        isLadderEnd = false;
        number = -1;
    }
};

#endif //PROJECT_CELL_H
