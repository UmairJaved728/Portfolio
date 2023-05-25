#include <iostream>
#include <fstream>
#include "Board.h"
#include "Player.h"

int printMainMenu();
void printHowToPlay();

int main() {
    Board *board;
    Player **players;
    int numOfPlayers, *positions, *playing, winCount, *winners, *playerNumbers, nextPosition, lost;
    int choice, size, numSnakes, numLadders, i, turn, dice, level;
    string name;
    bool isPlay, isLoad;
    char option;
    fstream file;

    do{
        choice = printMainMenu();
        isPlay = false;
        isLoad = false;
        level = 0;

        if(choice == 1) {
            numOfPlayers = 2;
            isPlay = true;
        }
        else if(choice == 2){
            do {
                cout << "Enter the Number of Players (3-9): ";
                cin >> numOfPlayers;
                if(cin.fail() || numOfPlayers < 3 || numOfPlayers > 9) {
                    cin.clear();
                    cin.ignore();
                    cout << "\nINVALID INPUT!!! Try Again...\n\n";
                }
            } while (numOfPlayers < 3 || numOfPlayers > 9 );
            isPlay = true;
            cout << '\n';
        }
        else if(choice == 3){
            level = 1;
            numOfPlayers = 2;
            isPlay = true;
        }
        else if(choice == 4){
            printHowToPlay();
        }
        else if(choice == 5){
            cout << "\n\t*** LOAD THE GAME ***\n\n";

            file.open("SnakeAndLadder.bin", ios::in | ios::binary);
            if(file.fail())
            {
                cout << "\nCannot Open this file or file does not exist... Save a Game first.\n\n";
            }
            else{
                file.read((char*)&size, sizeof(int));
                file.read((char*)&numOfPlayers, sizeof(int));
                board = new Board(size);
                players = new Player *[numOfPlayers];
                playing = new int[numOfPlayers];
                positions = new int[numOfPlayers];
                winners = new int[numOfPlayers];
                playerNumbers = new int[numOfPlayers];
                board->readBoard(file);
                for (i = 0; i < numOfPlayers; i++)
                    players[i] = new Player("", size);
                for(i=0; i<numOfPlayers; i++)
                    players[i]->readPlayer(file);
                file.read((char*)&winCount, sizeof(int));
                file.read((char*)winners, sizeof(int)*numOfPlayers);
                file.read((char*)playing, sizeof(int)*numOfPlayers);
                file.read((char*)&turn, sizeof(int));
                file.close();
                isPlay = true;
                isLoad = true;
            }
        }

        while(isPlay){
            if(!isLoad) {
                cout << "\t*** Setting Up The Game ***\n\n";
                do {
                    cout << "Default Board Configurtaions:\n";
                    cout << "\tBoard Size: 100\n";
                    cout << "\tNumber of Ladders: 3\n";
                    cout << "\tNumber of Snakes: 3\n";
                    cout << "\nDo you want to change Default Configurations? [Y/N]: ";
                    cin >> option;
                    option |= 32;
                    if (option != 'n' && option != 'y')
                        cout << "\nINVALID INPUT!!! Try Again...\n\n";
                } while (option != 'n' && option != 'y');

                if (option == 'y') {
                    do {
                        cout << "\nBoard size must be greater than or equal to 50 and multiple of 10.\n";
                        cout << "Enter board size: ";
                        cin >> size;
                        if (cin.fail() || size % 10 != 0 || size < 50) {
                            cin.clear();
                            cin.ignore();
                            cout << "\nINVALID INPUT!!! Try Again...\n";
                            size = 0;
                        }
                    } while (size % 10 != 0 || size < 50);

                    do {
                        cout << "\nEnter Number of Ladders (0-5): ";
                        cin >> numLadders;
                        if (cin.fail() || numLadders < 0 || numLadders > 5) {
                            cin.clear();
                            cin.ignore();
                            cout << "\nINVALID INPUT!!! Try Again...\n";
                            numLadders = -1;
                        }
                    } while (numLadders < 0 || numLadders > 5);

                    do {
                        cout << "\nEnter Number of Snakes (0-5): ";
                        cin >> numSnakes;
                        if (cin.fail() || numSnakes < 0 || numSnakes > 5) {
                            cin.clear();
                            cin.ignore();
                            cout << "\nINVALID INPUT!!! Try Again...\n";
                            numSnakes = -1;
                        }
                    } while (numSnakes < 0 || numSnakes > 5);
                } else {
                    size = 100;
                    numLadders = 3;
                    numSnakes = 3;
                }

                board = new Board(size);
                board->initializeBoard(numSnakes, numLadders);

                players = new Player *[numOfPlayers];
                playing = new int[numOfPlayers];
                positions = new int[numOfPlayers];
                winners = new int[numOfPlayers];
                playerNumbers = new int[numOfPlayers];

                cout << "\n";
                cin.ignore();
                for (i = 0; i < numOfPlayers; i++) {
                    cout << "Enter Name of Player " << i + 1 << ": ";
                    getline(cin, name, '\n');
                    players[i] = new Player(name, size);
                    playing[i] = 1;
                }
                turn = 0;
                winCount = 0;
            }

            cout << "\n\t*** PLAY GAME ***\n\n";
            if(level > 0)
                cout << "\t*** Level : " << level << " ***\n\n";
            lost = -1;

            do{
                cout << "\t\tCurrent Board";
                for(i=0; i<numOfPlayers; i++) {
                    positions[i] = players[i]->getLastPosition();
                    playerNumbers[i] = i+1;
                }
                board->printBoard(positions, playerNumbers, numOfPlayers);
                cout << "\nPoints:-\n";
                for(i=0; i<numOfPlayers; i++)
                    cout << players[i]->getName() << ": " << players[i]->getPoints() << '\t';
                cout << "\n\n";
                do {
                    cout << "It's " << players[turn]->getName() << "\'s turn:\tCurrent Position: " << players[turn]->getLastPosition() << '\n';
                    cout << "\t--> Enter \'r\' to Roll Dice.\n";
                    cout << "\t--> Enter \'e\' to End the Game. [You will lose]\n";
                    cout << "\t--> Enter \'s\' to Save the Game.\n\n";
                    cout << "\t\tEnter your choice: ";
                    cin >> option;
                    option |= 32;
                    if(option != 'r' && option != 's' && option != 'e')
                        cout << "\nINVALID INPUT!!! Try Again...\n";
                }while(option != 'r' && option != 's' && option != 'e');

                if(option == 'r'){
                    cout << "\n\tRolling Dice...\n";
                    dice = rand() % 6 + 1;
                    cout << "\tYou got " << dice << "\n";
                    cout << "\tMoving Piece...\n";
                    nextPosition = board->getNextPosition(players[turn]->getLastPosition(), dice );
                    if(nextPosition + dice < players[turn]->getLastPosition()){
                        cout << "\nOOPS! You stepped on a Snake. 50 points deducted.\n";
                        players[turn]->atSnake();
                    }
                    else if(nextPosition > players[turn]->getLastPosition() + dice){
                        cout << "\nWoah! You got a Ladder. 50 points added.\n";
                        players[turn]->atLadder();
                    }
                    else if(nextPosition == size){
                        cout << "\n\nCongratulations!! " << players[turn]->getName() << " completed the Board.\n\n";
                        playing[turn] = 0;
                        winners[winCount] = turn;
                        winCount++;
                        if(winCount == numOfPlayers - 1)
                            lost = 1;
                    }

                    players[turn]->addTurn(nextPosition, dice);
                    cout << "Turn Completed.\n";
                    cout << "New Position: " << nextPosition << "\n\n";
                    if(dice == 6 && players[turn]->getLastPosition() != size){
                        cout << "You got a 6, it's your turn again.\n\n";
                    }
                    else {
                        do {
                            turn = (turn + 1) % numOfPlayers;
                        } while (playing[turn] == 0);
                    }
                    if(lost == 1) {
                        lost = turn;
                    }
                    system("Pause");
                }
                else if(option == 'e'){
                    lost = turn;
                    while(winCount != numOfPlayers - 1){
                        do {
                            turn = (turn + 1) % numOfPlayers;
                        }while(playing[turn] == 0);
                        winners[winCount] = turn;
                        playing[turn] = 0;
                        winCount++;
                    }

                    winCount = numOfPlayers - 1;
                }
                else if(option == 's'){
                    cout << "\n\t*** SAVE THE GAME ***\n\n";
                    file.open("SnakeAndLadder.bin", ios::out | ios::binary);
                    file.write((char*)&size, sizeof(int));
                    file.write((char*)&numOfPlayers, sizeof(int));
                    board->writeBoard(file);
                    for(i=0; i<numOfPlayers; i++)
                        players[i]->writePlayer(file);
                    cout << "--\n\n";
                    file.write((char*)&winCount, sizeof(int));
                    file.write((char*)winners, sizeof(int)*numOfPlayers);
                    file.write((char*)playing, sizeof(int)*numOfPlayers);
                    file.write((char*)&turn, sizeof(int));
                    file.close();
                }
            }while(winCount != numOfPlayers - 1);

            cout << "Game Ended.\n\n";
            cout << "\t*** GAME STATS ***\n\n";

            cout << "  Position  |\t\tName\t\t|\tScore\n";
            cout << "------------------------------------------------------------\n\n";
            for(i=0; i<numOfPlayers-1; i++){
                switch(i){
                    case 0:
                        cout << "    First   |";
                        break;
                    case 1:
                        cout << "   Second   |";
                        break;
                    case 2:
                        cout << "    Third   |";
                        break;
                    case 3:
                        cout << "    Forth   |";
                        break;
                    case 4:
                        cout << "    Fifth   |";
                        break;
                    case 5:
                        cout << "    Sixth   |";
                        break;
                    case 6:
                        cout << "  Seventh   |";
                        break;
                    case 7:
                        cout << "   Eighth   |";
                        break;
                    case 8:
                        cout << "    Ninth   |";
                        break;
                }
                cout << "\t\t" <<  players[winners[i]]->getName() << "\t|\t" << players[winners[i]]->getPoints() << "\n";
            }
            cout << "\n";
            cout << players[lost]->getName() << " lost the Game.\nBetter Luck Next Time.\n\n";
            cout << "---------------------------------------------------\n\n";
            system("pause");

            if(level > 0){
                do{
                    cout << "\nDo you want to play Next Level with increased difficulty [Y/N]: ";
                    cin >> option;
                    option |= 32;
                    if (option != 'n' && option != 'y')
                        cout << "\nINVALID INPUT!!! Try Again...\n\n";
                } while (option != 'n' && option != 'y');

                if(option == 'y'){
                    isLoad = true;
                    delete board;
                    board = new Board(size);
                    numSnakes++;
                    numLadders--;
                    if(numLadders < 0)
                        numLadders = 0;
                    board->initializeBoard(numSnakes, numLadders);
                    level++;
                    for (i = 0; i < numOfPlayers; i++) {
                        playing[i] = 1;
                    }
                    Player** newP = new Player*[numOfPlayers];
                    for(i=0; i<numOfPlayers; i++){
                        newP[i] = new Player(players[i]->getName(), size);
                        delete players[i];
                    }
                    delete[] players;
                    players = newP;
                    winCount = 0;
                }
                else{
                    delete[] players;
                    delete[] playing;
                    delete[] positions;
                    delete[] winners;
                    delete[] playerNumbers;
                    isPlay = false;
                }
            }
            else {
                delete[] players;
                delete[] playing;
                delete[] positions;
                delete[] winners;
                delete[] playerNumbers;
                delete board;
                isPlay = false;
            }
        }

    } while (choice != 6);

    cout << "\tExiting the Game...\n";
    cout << "\n\t  *** GOODBYE ***\n\n";
    system("pause");
    return 0;
}

int printMainMenu()
{
    int option;

    cout << "\n\n\t-------------------------------------------------------------";
    cout << "\n\t|\t---> WELCOME TO THE SNAKE AND LADDER GAME <---\t    |\n";
    cout << "\t-------------------------------------------------------------\n\n";

    do{
        cout << "\t Enter [1] to Quick Play.\n";
        cout << "\t Enter [2] to play with more players.\n";
        cout << "\t Enter [3] to Play Continous\n";
        cout << "\t Enter [4] to view \"How to Play\".\n";
        cout << "\t Enter [5] to load a game.\n";
        cout << "\t Enter [6] to quit\n";

        cout << "\n\t\tEnter you choice: ";
        cin >> option;

        if(cin.fail() || option < 1 || option > 6) {
            cin.clear();
            cin.ignore();
            option = 0;
            cout << "\nINVALID INPUT!!! Try Again...\n\n";
        }
    }while(option < 1 || option > 6);
    cout << "\n";

    return option;
}

void printHowToPlay()
{
    cout << "\t*** HOW TO PLAY ***\n\n";
    cout << "* You are provided with a main menu.\n";
    cout << "* The Quick play option will start the simple game with 2 players.\n";
    cout << "* In Multiplayer option, you can choose the number of players from 3 upto 10.\n";
    cout << "* Next, You will enter the board size and the number of ladders and snakes.\n";
    cout << "* The board size must be greater than or equal to 50 and must be the multiple of 10.\n";
    cout << "* The number of snakes and ladders must be greater than equal to 2.\n";
    cout << "* The player who reaches the last cell of the board first, wins.\n";
    cout << "* The player can enter \'r\' to roll the dice or \'q\'  to quit.\n";
    cout << "* The player who quits the game loses.\n";
    cout << "* Player will be given extra turn on getting a 6.\n";
    cout << "* Bounce back rule is implemented such that if a player is at 98\n";
    cout << "* and he\\she gets a 6, 2 will be added to 100 and remaining will be subtracted.\n";
    cout << "* Each ladder will give a player 50 points.\n";
    cout << "* Each snake will decrement the 50 point.\n";
    cout << "* Otherwise each dice value will be added to the score\n";
    cout << "* Player can enter \'s\' to save the game anytime.\n";
    cout << "* Game stats will be shown at the end of each game.\n";
    cout << "-------------------------------------------------------------------------------------\n\n";
    system("pause");
}