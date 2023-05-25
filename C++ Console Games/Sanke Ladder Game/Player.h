
#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <iostream>

using namespace std;

class Player{
    string name;
    int points;
    int *stack;
    int capacity;
    int stackSize;
public:

    Player(string name, int boardSize);
    ~Player();
    void addTurn(int newPosition, int dice);
    void atSnake();
    void atLadder();
    string getName() const;
    int getPoints() const;
    void writePlayer(ostream& file);
    void readPlayer(istream& file);
    int getLastPosition();
};

#endif //PROJECT_PLAYER_H
