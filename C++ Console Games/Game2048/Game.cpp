#include<iostream>
#include<fstream>
#include "Game.h"

using namespace std;

Game::Game() = default;

void Game::play(){
    char input;
    bool newGame, isQuit = false;
    fstream hallOfFame;
    string name;
    int r = -1, c = -1, moves;

    hall.loadData();
    initBoard();
    printRules();

    do{
        printControls();
        printBoard();
        input = promptInput();
        moves = 0;
        newGame = false;
        switch (input) {
            case 'w':
                moves = moveUp();
                break;
            case 'x':
                moves = moveDown();
                break;
            case 'a':
                moves = moveLeft();
                break;
            case 'd':
                moves = moveRight();
                break;
            case 'n':
                if(confirm()) {
                    initBoard();
                    newGame = true;
                    moves = 1;
                }
                break;
            case 's':
                if(confirm()) {
                    saveGame();
                    moves = 1;
                    newGame = true;
                }
                break;
            case 'l':
                if(confirm()) {
                    loadGame();
                    newGame = true;
                    moves = 1;
                }
                break;
            case 'h':
                if(confirm()) {
                    hall.printHallOfFame();
                }
                break;
            case 'q':
                if(confirm()) {
                    isQuit = true;
                }
                break;
            default:
                cout << "Unexpected Error! This should never run!!\n\n";
                break;
        }

        if(isWin()){
            cout << "\nCongratulations!! You Won 2048 Game.\n\n";
        }
        else if(moves == 0){
            cout << "\nCannot move tiles in this Direction. Try Again!\n\n";
        }
        else if(!newGame) {
            getRandomEmptyCell(r, c);
            placeNewTile(r, c);
        }
    }while(!isGameOver() && !isWin() && !isQuit);

    printBoard();

    if(isWin())
        hall.addRecord(points);

    hall.printHallOfFame();
    cout << "\nExiting Game...\n\nGoodBye!\n\n";
}

void Game::loadGame() {
    int i, j, index;
    string filename;
    fstream file;
    char temp;

    cout << "\nPlease enter the Name of the file below, from where you want to load the Game contents.\n";
    cout << "CAUTION: Current Game contents will be lost.\n\n";
    cout << "Enter Filename: ";
    cin >> filename;

    file.open(filename, ios::in);

    if(file.fail()){
        cout << "Permission Denied! File does not exist or Cannot open this file.\n";
        cout << "Returning to Previous Game.\n\n";
        return;
    }

    for(i=0; i<6; i++)
        file >> temp;

    file >> points;

    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++) {
            file >> index;
            file >> temp;
            file >> grid[i][j].value;
        }
    file.close();

    cout << "Game is Loaded Successfully.\n\n";
}

void Game::saveGame() {
    int i, j;
    string filename;
    fstream file;
    cout << "\nPlease enter the Name of the file below, where you want to save the current Game contents.\n";
    cout << "CAUTION: Previous contents of the file will be deleted.\n\n";
    cout << "Enter Filename: ";
    cin >> filename;

    file.open(filename, ios::out);

    if(file.fail()){
        cout << "Permission Denied! cannot create or edit this file.\n\n";
        return;
    }

    file << "Score:" << points << '\n';
    for(i=0; i<ROWS; i++)
        for(j=0; j<COLS; j++)
            file << i*COLS+j << ':' << grid[i][j].value << '\n';
    file.close();

    cout << "Game is saved.\n\n";
}

void Game::printRules() {

    cout << "\n\t    ***     ****   *   *   **** \n";
    cout << "\t   *   *   *    *  *   *  *    * \n";
    cout << "\t       *   *    *  *****  * ** * \n";
    cout << "\t     *     *    *      *  *    * \n";
    cout << "\t   ******   ****       *   ****  \n";

    cout << "\n                   ***  RULES ***                         \n";
    cout << "\n2048 is played on a plain " << ROWS << " x " << COLS << " grid,\n";
    cout << "with numbered tiles that slide when a player moves them using the four arrow keys. \n";
    cout << "Every turn, a new tile randomly appears in an empty spot on the board with a value of either 2 or 4. \n";
    cout << "Tiles slide as far as possible in the chosen direction until they are stopped by either another tile \n";
    cout << "or the edge of the grid. If two tiles of the same number collide while moving, they will merge into a tile \n";
    cout << "with the total value of the two tiles that collided.\n";
}

void Game::printControls()
{
    cout << "\n-- How to interact? You can enter one of these letters any time in the game.\n\n";
    cout << "--> Enter \'N\' or \'n\' - Start a new game\n";
    cout << "--> Enter \'S\' or \'s\' - Save the game\n";
    cout << "--> Enter \'L\' or \'l\' - Load a game\n";
    cout << "--> Enter \'H\' or \'h\' - Display the hall of fame\n";
    cout << "--> Enter \'Q\' or \'q\' - Quit\n\n";
}

char Game::promptInput(){
    char choice;
    bool isDone = false;

    do{
        cout << '\n';
        cout << " --> Enter \'W\' or \'w\' - Slide Up\n";
        cout << " --> Enter \'X\' or \'x\' - Slide Down\n";
        cout << " --> Enter \'A\' or \'a\' - Slide Left\n";
        cout << " --> Enter \'D\' or \'d\' - Slide Right\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        choice |= 32;

        if(cin.fail() || (choice != 'w' && choice != 'x' && choice != 'a' && choice != 'd' && choice != 'n' && choice != 's' && choice != 'l' && choice != 'h' && choice != 'q'))
        {
            cin.ignore();
            cin.clear();
            cout << "\nInvalid Input!! Try Again...\n";
        }
        else
            isDone = true;

    }while(!isDone);

    return choice;
}
