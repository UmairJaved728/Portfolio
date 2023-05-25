//
// Created 12/30/2022.
//

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include "Game2048.h"

using namespace std;

Game2048::Game2048() {
    points = 0;
}

void Game2048::printBoard()
{
    int i, j;
    cout << "\n+";
    for(i=0; i<COLS; i++)
       cout << "----+";

    for(i=0; i<ROWS; i++){
        cout << "\n|";
        for(j=0; j<COLS; j++){
            if(grid[i][j].isMine)
                cout << "   *";
            else if(grid[i][j].value == 0)
                cout << "    ";
            else
                cout << fixed << setw(4) << grid[i][j].value;
            cout << "|";
        }
        cout << "\n+";
        for(j=0; j<COLS; j++)
            cout << "----+";
    }
    cout << "\n\n";
    cout << "\n\tPoints: " << points << "\n\n";
}

void Game2048::placeNewTile(int r, int c)
{
    int prob;
    prob = rand() % 10 + 1;

    if(prob <= 4)
        grid[r][c].value = 2;
    else if(prob <= 8)
        grid[r][c].value = 4;
    else
    {
        grid[r][c].isMine = true;
        grid[r][c].value = 0;
    }

}

void Game2048::resetBoard() {
    int i, j;

    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++){
            grid[i][j].value = 0;
            grid[i][j].isMine = false;
            grid[i][j].isCombined = false;
        }
}

void Game2048::initBoard(){
    srand(time(0));
    int r, c;

    resetBoard();
    points = 0;

    r = rand() % ROWS;
    c = rand() % COLS;

    placeNewTile(r, c);

    while(grid[r][c].value != 0 || grid[r][c].isMine) {
        r = rand() % ROWS;
        c = rand() % COLS;
    }

    placeNewTile(r, c);
}

void Game2048::getRandomEmptyCell(int &r, int &c){
    int count, i, j;

    if(isGameOver())
        return;

    do{
        count = 0;
        r = rand() % ROWS;
        for(i=0; i<COLS; i++)
            if(grid[r][i].value != 0 || grid[r][i].isMine)
                count++;
    }while(count == COLS);

    do{
        c = rand() % COLS;
    }while(grid[r][c].value != 0 || grid[r][c].isMine);
}

void Game2048::readyBoard()
{
    int i, j;
    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
            grid[i][j].isCombined = false;
}

int Game2048::moveUp(){
    int i, j, k, moves = 0;
    readyBoard();

    for(j=0; j<COLS; j++)
    {
        for(k = 0; k < ROWS; k++) {
            i = k;
            while (i < ROWS && grid[i][j].value == 0 && !grid[i][j].isMine )
                i++;

            if (i == ROWS)
                continue;

            while(i > 0)
            {
                if(grid[i-1][j].value != 0)
                {
                    if(grid[i][j].isMine && !grid[i-1][j].isCombined)
                    {
                        grid[i][j].isMine = false;
                        points -= grid[i-1][j].value;
                        if(points < 0)
                            points = 0;
                        grid[i-1][j].value = 0;
                        moves++;
                    }
                    else if(grid[i][j].value == grid[i-1][j].value && !grid[i-1][j].isCombined && !grid[i][j].isCombined) {
                        grid[i][j].value = 0;
                        grid[i - 1][j].value *= 2;
                        grid[i - 1][j].isCombined = true;
                        points += grid[i-1][j].value;
                        moves++;
                    }
                }
                else{
                    if(grid[i-1][j].isMine){
                        grid[i-1][j].isMine = false;
                        points -= grid[i][j].value;
                        if(points < 0)
                            points = 0;
                        grid[i][j].value = 0;
                    }
                    else{
                        grid[i-1][j].value = grid[i][j].value;
                        grid[i-1][j].isCombined = grid[i][j].isCombined;
                        grid[i-1][j].isMine = grid[i][j].isMine;
                        grid[i][j].value = 0;
                        grid[i][j].isMine = false;
                        grid[i][j].isCombined= false;
                    }
                    moves++;
                }
                i--;
            }
        }
    }
    return moves;
}

int Game2048::moveDown(){
    int i, j, k, moves = 0;

    readyBoard();
    for(j=0; j<COLS; j++)
    {
        for(k = ROWS-1; k >= 0; k--) {
            i = k;
            while (i >= 0 && grid[i][j].value == 0 && !grid[i][j].isMine )
                i--;

            if (i < 0)
                continue;

            while(i < ROWS-1)
            {
                if(grid[i+1][j].value != 0)
                {
                    if(grid[i][j].isMine && !grid[i+1][j].isCombined)
                    {
                        grid[i][j].isMine = false;
                        points -= grid[i+1][j].value;
                        if(points < 0)
                            points = 0;
                        grid[i+1][j].value = 0;
                        moves++;
                    }
                    else if(grid[i][j].value == grid[i+1][j].value && !grid[i+1][j].isCombined && !grid[i][j].isCombined) {
                        grid[i][j].value = 0;
                        grid[i + 1][j].value *= 2;
                        points += grid[i+1][j].value;
                        grid[i + 1][j].isCombined = true;
                        moves++;
                    }
                }
                else{
                    if(grid[i+1][j].isMine){
                        grid[i+1][j].isMine = false;
                        points -= grid[i][j].value;
                        if(points < 0)
                            points = 0;
                        grid[i][j].value = 0;
                    }
                    else{
                        grid[i+1][j].value = grid[i][j].value;
                        grid[i+1][j].isCombined = grid[i][j].isCombined;
                        grid[i+1][j].isMine = grid[i][j].isMine;
                        grid[i][j].value = 0;
                        grid[i][j].isMine = false;
                        grid[i][j].isCombined= false;
                    }
                    moves++;
                }
                i++;
            }
        }
    }
    return moves;
}
int Game2048::moveLeft(){
    int i, j, k, moves = 0;
    readyBoard();

    for(i=0; i<ROWS; i++)
    {
        for(k = 0; k < COLS; k++) {
            j = k;
            while (j < COLS && grid[i][j].value == 0 && !grid[i][j].isMine )
                j++;

            if (j == COLS)
                continue;

            while(j > 0)
            {
                if(grid[i][j-1].value != 0)
                {
                    if(grid[i][j].isMine && !grid[i][j-1].isCombined)
                    {
                        grid[i][j].isMine = false;
                        points -= grid[i][j-1].value;
                        if(points < 0)
                            points = 0;
                        grid[i][j-1].value = 0;
                        moves++;
                    }
                    else if(grid[i][j].value == grid[i][j-1].value && !grid[i][j-1].isCombined && !grid[i][j].isCombined) {
                        grid[i][j].value = 0;
                        grid[i][j-1].value *= 2;
                        points += grid[i][j-1].value;
                        grid[i][j-1].isCombined = true;
                        moves++;
                    }
                }
                else{
                    if(grid[i][j-1].isMine){
                        grid[i][j-1].isMine = false;
                        points -= grid[i][j].value;
                        if(points < 0)
                            points = 0;
                        grid[i][j].value = 0;
                    }
                    else{
                        grid[i][j-1].value = grid[i][j].value;
                        grid[i][j-1].isCombined = grid[i][j].isCombined;
                        grid[i][j-1].isMine = grid[i][j].isMine;
                        grid[i][j].value = 0;
                        grid[i][j].isMine = false;
                        grid[i][j].isCombined= false;
                    }
                    moves++;
                }
                j--;
            }
        }
    }
    return moves;
}
int Game2048::moveRight(){
    int i, j, k, moves = 0;
    readyBoard();

    for(i=ROWS-1; i>=0; i--)
    {
        for(k = COLS-1; k >= 0; k--) {
            j = k;
            while (j >= 0 && grid[i][j].value == 0 && !grid[i][j].isMine )
                j--;

            if (j < 0)
                continue;

            while(j < COLS-1)
            {
                if(grid[i][j+1].value != 0)
                {
                    if(grid[i][j].isMine && !grid[i][j+1].isCombined)
                    {
                        grid[i][j].isMine = false;
                        points -= grid[i][j+1].value;
                        if(points < 0)
                            points = 0;
                        grid[i][j+1].value = 0;
                        moves++;
                    }
                    else if(grid[i][j].value == grid[i][j+1].value && !grid[i][j+1].isCombined && !grid[i][j].isCombined) {
                        grid[i][j].value = 0;
                        grid[i][j+1].value *= 2;
                        points += grid[i][j+1].value;
                        grid[i][j+1].isCombined = true;
                        moves++;
                    }
                }
                else{
                    if(grid[i][j+1].isMine){
                        grid[i][j+1].isMine = false;
                        points -= grid[i][j].value;
                        if(points < 0)
                            points = 0;
                        grid[i][j].value = 0;
                    }
                    else{
                        grid[i][j+1].value = grid[i][j].value;
                        grid[i][j+1].isCombined = grid[i][j].isCombined;
                        grid[i][j+1].isMine = grid[i][j].isMine;
                        grid[i][j].value = 0;
                        grid[i][j].isMine = false;
                        grid[i][j].isCombined= false;
                    }
                    moves++;
                }
                j++;
            }
        }
    }
    return moves;
}


bool Game2048::isWin(){
    int i, j;

    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
            if(grid[i][j].value == 2048)
                return true;
    return false;
}

bool Game2048::isGameOver(){
    int count = 0;
    int i, j;

    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
            if(grid[i][j].value != 0)
                count++;

    if(count == ROWS*COLS)
        return true;
    return false;
}
