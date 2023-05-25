#include <iostream>
#include <utility>
#include "Player.h"

using namespace std;

Player::Player(string name, int boardSize){
    this->name = name;
    this->points = 0;
    this->capacity = boardSize + 1;
    this->stack = new int[boardSize+1];
    this->stack[0] = 1;
    this->stackSize = 1;
}

Player::~Player(){
    delete[] stack;
}

void Player::addTurn(int newPosition, int dice){
    this->stack[stackSize] = newPosition;
    stackSize++;
    this->points += dice;
}

int Player::getLastPosition(){
    return stack[stackSize-1];
}

void Player::atSnake(){
    this->points -= 50;
}
void Player::atLadder(){
    this->points += 50;
    if(points < 0)
        points = 0;
}

int Player::getPoints() const{
    return points;
}

string Player::getName() const{
    return name;
}

void Player::writePlayer(ostream& file){
    file.write(name.c_str(), name.size());
    file.write("\n",sizeof(char));
    file.write((char*)&points, sizeof(int));
    file.write((char*)&stackSize, sizeof(int));
    file.write((char*)stack, sizeof(int)*capacity);
}

void Player::readPlayer(istream &file) {
    getline(file, name, '\n');
    file.read((char*)&points, sizeof(int));
    file.read((char*)&stackSize, sizeof(int));
    file.read((char*)stack, sizeof(int)*capacity);
}