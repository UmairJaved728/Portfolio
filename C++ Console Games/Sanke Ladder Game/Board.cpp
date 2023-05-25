#include <iostream>
#include <iomanip>
#include "Board.h"

using namespace std;

Board::Board(int size)
{
    srand(time(nullptr));
    this->size = size;
    this->cols = 10;
    this->rows = size / 10;
    board = new Cell[size];
}

void Board::initializeBoard(int numOfSnakes, int numOfLadders) {
    int i, j, value = 1;
    for(i=0; i<size; i++){
            board[i].value = value++;
    }
    setLadders(numOfLadders);
    setSnakes(numOfSnakes);
}

void Board::setLadders(int numOfLadders){
    int count, start, end, index, j;
    bool isDone;
    for(count = 0; count < numOfLadders; count++)
    {
        isDone = false;
        do{
            start = rand() % ((size - cols - 3) - 3) + 3;

            if( !board[start].isLadder && !board[start].isSnake )
            {
                index = start / cols;
                for( j = 0; j < cols; j++)
                    if(board[index*cols+j].isLadderStart) {
                        break;
                    }

                if( j == cols ) {
                    isDone = true;
                    end = 0;
                    while (end <= start + cols) {
                        end = rand() % size;
                    }
                    board[start].isLadder = true;
                    board[start].isLadderStart = true;
                    board[end].isLadder = true;
                    board[end].isLadderEnd = true;
                    board[start].number = count+1;
                    board[end].number = count+1;
                }
            }

        }while(!isDone);
    }
}

void Board::setSnakes(int numOfSnakes){
    int count, start, end, index, j;
    bool isDone;
    for(count = 0; count < numOfSnakes; count++)
    {
        isDone = false;
        do{
            start = rand() % ( (size-3) - (cols + 3) ) + (cols+3);
            if(start > size)
                start -= cols;

            if( !board[start].isLadder && !board[start].isSnake )
            {
                index = start / cols;
                for( j = 0; j < cols; j++)
                    if(board[index*cols+j].isSnakeStart) {
                        break;
                    }

                if( j == cols ) {
                    isDone = true;
                    end = size-1;
                    while (end >= start - cols) {
                        end = rand() % size;
                    }

                    board[start].isSnake = true;
                    board[start].isSnakeStart = true;
                    board[start].number = count+1;
                    board[end].isSnake = true;
                    board[end].isSnakeEnd = true;
                    board[end].number = count+1;
                }
            }

        }while(!isDone);
    }
}

void Board::printBoard(int *playerPosition, int *playerNumbers, int numOfPlayers) {
    int i, j, c;
    cout << "\n\n";
    for(i=0; i<cols; i++)
        cout << "|++++++";
    cout << "|\n";

    for(i=rows-1; i>=0; i--) {
        for (j = 0; j < cols; j++){
            cout << "|";
            c = 0;
            for(int k = 0; k<numOfPlayers; k++) {
                if (i * cols + j + 1 == playerPosition[k]) {
                    if(c == 3){
                        cout << "|";
                        for(int m=0; m<cols-1; m++)
                            cout << "      |";
                        cout << "\n|";
                        c = 0;
                    }
                    cout << "P" << playerNumbers[k];
                    c++;
                }
            }
            for(int k=c*2; k<6; k++)
                cout << " ";
        }
        cout << "|\n";

        for (j = 0; j < cols; j++){
            cout << "|";
            cout << fixed << setw(4) << board[i*cols+j].value;
            cout << "  ";
        }
        cout << "|\n";

        for (j = 0; j < cols; j++){
            cout << "|";
            if(board[i*cols+j].isLadder){
                cout << " L" << board[i*cols+j].number;
                if(board[i*cols+j].isLadderStart)
                    cout << "_s ";
                else
                    cout << "_e ";
            }
            else if(board[i*cols+j].isSnake){
                cout << " S" << board[i*cols+j].number;
                if(board[i*cols+j].isSnakeStart)
                    cout << "_s ";
                else
                    cout << "_e ";
            }
            else
                cout << "      ";
        }

        cout << "|\n";
        for(j=0; j<cols; j++)
            cout << "|++++++";
        cout << "|\n";
    }
}

int Board::getNextPosition(int currentPosition, int dice){
    int newPosition = currentPosition + dice, n, i;
    if(newPosition > size){
        cout << "\tYou went out of the board.\n";
        cout << "\tRolling back " << newPosition - size << " cells.\n";
        return size - (newPosition - size);
    }
    else if( board[newPosition-1].isSnakeStart ){
        n = board[newPosition-1].number;
        for(i = 0; i < size; i++)
            if(board[i].isSnakeEnd && board[i].number == n)
                return board[i].value;
    }
    else if( board[newPosition-1].isLadderStart ){
        n = board[newPosition-1].number;
        for(i = 0; i < size; i++)
            if(board[i].isLadderEnd && board[i].number == n)
                return board[i].value;
    }

    return newPosition;
}

void Board::writeBoard(ostream &file){
    file.write((char*)&size, sizeof(int));
    file.write((char*)&rows, sizeof(int));
    file.write((char*)&cols, sizeof(int));
    file.write((char*)board, sizeof(Cell) * size);
}

void Board::readBoard(istream &file){
    file.read((char*)&size, sizeof(int));
    file.read((char*)&rows, sizeof(int));
    file.read((char*)&cols, sizeof(int));
    file.read((char*)board, sizeof(Cell) * size);
}

Board::~Board(){
    int i;
    delete[] board;
}