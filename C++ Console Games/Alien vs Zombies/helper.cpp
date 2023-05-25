//helper
#ifndef PF_HELPER
#define PF_HELPER

#include "helper.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace pf {
    int kRows = 5;
    int kColumns = 9;
    int zombie_count = 3;

    struct Cell {
        int is_rock;
        int pod;
        int power_up;
        int arrow; // 0 = no arrow, 1 = up, 2 = right, 3 = down, 4 = left
        int is_health;
        bool is_zombie;
        bool is_alien;
        bool is_empty;
        char representation;
    };

    struct Character {
        int row_no;
        int col_no;
        int life;
        int attack;
        int range;
        bool isAlive;
        char representation;
    };

    void PrintGameSettings() {
        std::cout << "Default Game Settings";
        std::cout << "\n--------------------\n";
        std::cout << "Board Rows     : " << kRows << std::endl;
        std::cout << "Board Columns  : " << kColumns << std::endl;
        std::cout << "Zombie Count   : " << zombie_count << std::endl;
    }

    void ChangeGameSettings() {
        int z_count;

        ClearScreen();
        std::cout << "Board Settings\n";
        std::cout << "--------------------\n";
        do {
            std::cout << "Enter rows => ";
            std::cin >> kRows;
            if (std::cin.fail() || kRows < 3 || kRows % 2 == 0) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "\nInvalid Input!! Enter an odd number, must be greater than 3.\n\n";
            }
        } while (kRows < 3 || kRows % 2 == 0);

        do {
            std::cout << "Enter Columns => ";
            std::cin >> kColumns;
            if (std::cin.fail() || kColumns < 3 || kColumns % 2 == 0) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "\nInvalid Input!! Enter an odd number, must be greater than 3.\n\n";
            }
        } while (kColumns < 3 || kColumns % 2 == 0);

        std::cout << "\nZombie Settings\n";
        std::cout << "---------------------";

        while (1) {
            std::cout << "\nEnter number of zombies(1-9): ";
            std::cin >> z_count;
            if (std::cin.fail() || z_count < 1 || z_count > 9) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "\nInvalid Input! Zombies can only be in range 1-9\n";
            } else {
                zombie_count = z_count;
                break;
            }
        }
        std::cout << "\nSettings Updated.\n\n";
        Pause();
    }

    void Help() {
        std::cout << "\nCommands\n";
        std::cout << "up\t-Alien to move up\n";
        std::cout << "down\t-Alien to move down\n";
        std::cout << "left\t-Alien to move left\n";
        std::cout << "right\t-Alien to move right\n";
        std::cout << "arrow\t-Change the direction of an arrow\n";
        std::cout << "help\t-Display these user commands\n";
        std::cout << "save\t-Save the game\n";
        std::cout << "load\t-Load a game\n";
        std::cout << "quit\t-Quit the game\n\n";
        Pause();
    }

    Cell **board = NULL;
    Character alien;
    Character *zombies = NULL;

    int GameOver() {
        if (alien.life <= 0)   // alien dead
            return 2;

        for (int i = 0; i < zombie_count; i++)
            if (zombies[i].life > 0)      // zombie is still alive
                return false;

        return 1;        // all zombies are dead
    }

    void DeleteGameBoard() {
        int i;
        if (board != NULL) {
            for (i = 0; i < kRows; i++)
                delete[] board[i];
            delete[] board;
        }
        if (zombies != NULL)
            delete[] zombies;
    }

    void Caps_to_small(std::string &a) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] >= 65 && a[i] <= 90)
                a = a[i] + 32;
        }
    }

    void ChangeArrow() {
        int r_no, c_no;
        std::string direction;
        do {
            std::cout << "\nEnter Row Number => ";
            std::cin >> r_no;

            if (std::cin.fail() || r_no < 1 || r_no > kRows) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "\nInvalid Input!!\n";
            }
        } while (r_no < 1 || r_no > kRows);

        do {
            std::cout << "\nEnter Column Number => ";
            std::cin >> c_no;

            if (std::cin.fail() || c_no < 1 || c_no > kColumns) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "\nInvalid Input!!\n";
            }
        } while (c_no < 1 || c_no > kColumns);

        r_no--;
        c_no--;

        std::cin.ignore();
        do {
            std::cout << "\nEnter Direction => ";
            std::cin >> direction;

            Caps_to_small(direction);
            if (direction != "up" && direction != "down" && direction != "left" && direction != "right") {
                std::cout << "\nInvalid Input!!\n";
            }
        } while (direction != "up" && direction != "down" && direction != "left" && direction != "right");

        if (board[r_no][c_no].arrow) {
            if (direction == "up") {
                board[r_no][c_no].arrow = 1;
                board[r_no][c_no].representation = '^';
            } else if (direction == "right") {
                board[r_no][c_no].arrow = 2;
                board[r_no][c_no].representation = '>';
            } else if (direction == "down") {
                board[r_no][c_no].arrow = 3;
                board[r_no][c_no].representation = 'v';
            } else if (direction == "left") {
                board[r_no][c_no].arrow = 4;
                board[r_no][c_no].representation = '<';
            }
        } else {
            std::cout << "\nSelected Cell is not an arrow.\n\n";
        }
        std::cout << "\nArrow changed\n";
        pf::Pause();
        std::cin.ignore();
    }

    char isCharacter(int r_no, int c_no) {
        int i, j;
        if (board[r_no][c_no].representation == 'A') {
            return alien.representation;
        }

        for (i = 0; i < zombie_count; i++) {
            if (zombies[i].row_no == r_no && zombies[i].col_no == c_no) {
                return zombies[i].representation;
            }
        }
        return 'N';
    }

    void reset_cell(int i, int j){
        board[i][j].is_rock = 0;
        board[i][j].pod = 0;
        board[i][j].is_health = 0;
        board[i][j].is_zombie = false;
        board[i][j].is_alien = false;
        board[i][j].is_empty = false;
        board[i][j].arrow = 0;
        board[i][j].power_up=0;
    }

    void SetRandomObject(int i, int j, int num) {
        // assigning objects randomly
        // 1 : arrow up
        // 2 : arrow right
        // 3 : arrow down
        // 4 : arrow left
        // 5,6 : health
        // 7 : pod
        // 8: power up
        // 9 : rock
        // 10 : empty
        if (num >= 1 && num <= 4)  // arrow
        {
            reset_cell(i,j);
            board[i][j].arrow = num;

            if (num == 1)
                board[i][j].representation = '^';
            else if (num == 2)
                board[i][j].representation = '>';
            else if (num == 3)
                board[i][j].representation = 'v';
            else if (num == 4)
                board[i][j].representation = '<';
        }

        else if (num == 5 || num == 6) {
            reset_cell(i,j);
            board[i][j].representation = 'h';
            board[i][j].is_health = 20;
        }

        else if (num == 7) {
            reset_cell(i,j);
            board[i][j].pod = 10;
            board[i][j].representation = 'p';
        }

        else if (num == 8) {
            reset_cell(i,j);
            board[i][j].power_up = 10;
            board[i][j].representation = 'u';
        }

        else if (num == 9) {
            reset_cell(i,j);
            board[i][j].is_rock = rand() % 8 + 1;
            board[i][j].representation = 'r';
        }

        else {
            reset_cell(i,j);
            board[i][j].representation = ' ';
        }
    }

    void CreateGameBoard() {
        int i, j, r, c, num;
        // assigning the memory
        board = new Cell *[kRows];
        for (i = 0; i < kRows; i++)
            board[i] = new Cell[kColumns];
        zombies = new Character[zombie_count];

        // setting allien attributes
        alien.attack = 0;
        alien.row_no = kRows / 2;
        alien.col_no = kColumns / 2;
        alien.life = ((rand() % 5) * 50) + 200;    // between 100 and 300
        alien.range = 0;
        alien.representation = 'A';

        // Setting zombies attributes
        for (i = 0; i < zombie_count; i++) {
            zombies[i].life = ((rand() % 2) * 50) + 100;     // between 50 and 250
            zombies[i].attack = ((rand() % 5) * 10) + 10;
            zombies[i].row_no = -1;
            zombies[i].col_no = -1;
            zombies[i].range = rand() % std::min(kRows-1, kColumns-1) + 1;
            zombies[i].representation = (i + 1) + '0';
            zombies[i].isAlive = true;
        }

        // placing characters on board
        board[alien.row_no][alien.col_no].representation = alien.representation;
        board[alien.row_no][alien.col_no].is_alien = true;

        for (i = 0; i < zombie_count; i++) {
            do {
                r = rand() % kRows;
                c = rand() % kColumns;
            } while (isCharacter(r, c) != 'N');
            zombies[i].row_no = r;
            zombies[i].col_no = c;
            board[r][c].representation = zombies[i].representation;
            board[r][c].is_zombie = true;
        }

        // Placing Random Objects in the board
        for (i = 0; i < kRows; i++) {
            for (j = 0; j < kColumns; j++) {
                if (!(i == alien.row_no && j == alien.col_no))
                    board[i][j].is_alien = false;

                if (isCharacter(i, j) != 'N') {
                    continue;
                }
                int num = rand() % 10 + 1;  // generating random number from 1 to 10
                SetRandomObject(i, j, num);
            }
        }
    }

    void ShowGameBoard() {

        std::cout << "\t .: Alien vs Zombie :.\n\n";

        std::cout << std::setw(5) << std::right;

        int prefix = 1, f_cols = 1, no_cols = 9, no_col = 9;

        for (int i = 1; i <= 9 && f_cols <= kColumns; i++, f_cols++) { //displaying first 9 column numbers
            std::cout << i << " ";
        }

        for (int k = 1; k <= (kColumns / 10); k++) {
            for (int j = 0; j <= 9 && no_cols < kColumns; j++, no_cols++) { //displaying first digit
                std::cout << prefix << " ";
            }
            prefix++;
        }
        if (kColumns > 9)
            std::cout << std::endl;
        std::cout << std::setw(23) << std::right;
        for (int k = 1; k <= (kColumns / 10); k++) {
            for (int j = 0; j <= 9 && no_col < kColumns; j++, no_col++) { //displaying remaining digits
                std::cout << j << " ";
            }
        }

        //dislaying board
        std::cout << "\n";
        std::cout << std::setw(5);
        for (int i = 0; i < kColumns; i++) {
            std::cout << "+-";
        }
        std::cout << "+\n";
        for (int j = 0; j < kRows; j++) {
            std::cout << std::setw(3) << std::left << j + 1; //displaying rows
            for (int i = 0; i < kColumns; i++) {
                std::cout << "|" << board[j][i].representation;
            }
            std::cout << "| ";
            std::cout << std::endl;
            std::cout << std::setw(5) << std::right;
            for (int i = 0; i < kColumns; i++) { //displaying columns
                std::cout << "+-";
            }
            std::cout << "+\n";
        }

        std::cout << "\n\n";
    }

    int GetClosestZombie(int r, int c) {
        int i, minDistance = 99, minDisIndex, distance;
        for (i = 0; i < zombie_count; i++) {
            distance = std::min(abs(zombies[i].row_no - r), abs(zombies[i].col_no - c));
            if (minDistance > distance) {
                minDistance = distance;
                minDisIndex = i;
            }
        }
        return i;
    }

    bool CanAttack(int r, int c, int range) {
        if ((abs(r - alien.row_no) <= range) && (abs(c - alien.col_no) <= range))
            return true;
        return false;
    }

    void ResetTrail() {
        int i, j;
        for (i = 0; i < kRows; i++) {
            for (j = 0; j < kColumns; j++) {
                if (board[i][j].representation == '.') {
                    int num = rand() % 10 + 1;  // generating random number from 1 to 10
                    SetRandomObject(i, j, num);
                }
            }
        }
    }


    void Turn(int t) {
        if (t == 0)
            std::cout << "->";
        std::cout << "\tAlien\t: Life  " << alien.life << ", Attack  " << alien.attack << std::endl;
        for (int i = 0; i < zombie_count; i++) {
            if (t == i + 1)
                std::cout << "->\tZombie" << i + 1 << "\t: Life  " << zombies[i].life << ", Attack  "
                          << zombies[i].attack << ", Range  " << zombies[i].range << std::endl;
            else
                std::cout << "\tZombie" << i + 1 << "\t: Life  " << zombies[i].life << ", Attack  " << zombies[i].attack
                          << ", Range  " << zombies[i].range << std::endl;
        }
    }

    bool OutOfBound(int rows, int cols) {
        if (rows < 0 || rows >=kRows || cols < 0 || cols >=kColumns) {
            return true;
        }
        return false;
    }

    void ResetZombieAttributes(int zombie_no) {
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].representation = ' ';
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].is_rock = 0;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].pod = 0;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].is_health = 0;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].is_zombie = false;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].is_alien = false;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].is_empty = false;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].arrow = 0;
        board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].power_up = 0;
    }

    void ZombieMove() {
        int num;
        for (int zombie_no = 0; zombie_no < zombie_count; zombie_no++) {
            if( zombies[zombie_no].row_no == -1 )
                continue;
            ClearScreen();
            ShowGameBoard();
            Turn(zombie_no + 1);
            while (1) {
                num = rand() % 4; //generating random numbers from 0-3

                if (num == 0 && !OutOfBound(zombies[zombie_no].row_no - 1, zombies[zombie_no].col_no) &&
                    isCharacter(zombies[zombie_no].row_no - 1, zombies[zombie_no].col_no) == 'N') {
                    ResetZombieAttributes(zombie_no); //placing blank space in place of Zombie
                    zombies[zombie_no].row_no = zombies[zombie_no].row_no - 1; //move up 1 unit
                    std::cout << "\nZombie " << zombie_no + 1 << " moves up\n";
                    break;
                }

                else if (num == 1 && !OutOfBound(zombies[zombie_no].row_no, zombies[zombie_no].col_no + 1) &&
                           isCharacter(zombies[zombie_no].row_no, zombies[zombie_no].col_no + 1) == 'N') {
                    ResetZombieAttributes(zombie_no); //placing blank space in place of Zombie
                    zombies[zombie_no].col_no = zombies[zombie_no].col_no + 1;//move right 1 unit
                    std::cout << "\nZombie " << zombie_no + 1 << " moves right\n";
                    break;
                }

                else if (num == 2 && !OutOfBound(zombies[zombie_no].row_no + 1, zombies[zombie_no].col_no) &&
                           isCharacter(zombies[zombie_no].row_no + 1, zombies[zombie_no].col_no) == 'N') {
                    ResetZombieAttributes(zombie_no); //placing blank space in place of Zombie
                    zombies[zombie_no].row_no = zombies[zombie_no].row_no + 1; //move down 1 unit
                    std::cout << "\nZombie " << zombie_no + 1 << " moves down\n";
                    break;
                }

                else if (num == 3 && !OutOfBound(zombies[zombie_no].row_no, zombies[zombie_no].col_no - 1) &&
                           isCharacter(zombies[zombie_no].row_no, zombies[zombie_no].col_no - 1) == 'N') {
                    ResetZombieAttributes(zombie_no); //placing blank space in place of Zombie
                    zombies[zombie_no].col_no = zombies[zombie_no].col_no - 1;//move left 1 unit
                    std::cout << "\nZombie " << zombie_no + 1 << " moves left\n";
                    break;
                }
            }

            ResetZombieAttributes(zombie_no);
            board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].representation = (zombie_no + 1) + '0';
            board[zombies[zombie_no].row_no][zombies[zombie_no].col_no].is_zombie = true;

            Pause();
            ClearScreen();
            ShowGameBoard();
            Turn(zombie_no + 1);

            if (CanAttack(zombies[zombie_no].row_no, zombies[zombie_no].col_no, zombies[zombie_no].range)) {
                alien.life = alien.life - zombies[zombie_no].attack;
                std::cout << "Zombie " << zombie_no + 1 << " attacked Alien\n";
                if(alien.life <= 0)
                    alien.life = 0;
            }
            else
                std::cout << "\nZombie " << zombie_no + 1 << " is unable to attack Alien\nAlien is too far\n";
            Pause();
            ClearScreen();
            ShowGameBoard();
            Turn(zombie_no+1);
            std::cout << "\nZombie " << zombie_no + 1 << " turn ends\n";
        }
    }

    void DetectCell(int i, int j) {
        int index;
        if (board[i][j].representation == 'h') { //found health
            std::cout << "\nAlien finds a health Pack\n";
            std::cout << "Alien life is increased by 20\n";
            alien.life = alien.life + 20;
        }

        else if (board[i][j].representation == 'p') {//found pod
            std::cout << "\nAlien finds a pod\n";
            index = GetClosestZombie(i,j);
            zombies[index-1].life = zombies[index-1].life - board[i][j].pod;
            std::cout << "\nZombie " << index << " health reduced by " <<  board[i][j].pod << "\n";
            if(zombies[index-1].life <=0 ){
                std::cout << "\nZombie " << index<< " died\n";
                zombies[index-1].row_no = -1;
                zombies[index-1].col_no = -1;
                zombies[index-1].life = 0;
            }
        }

        else if (board[i][j].representation == 'u') {//found powerup
            std::cout << "\nAlien finds a power up\n";
            std::cout << "\nAll zombies health reduced by " <<  board[i][j].power_up << "\n";
            for(int i=0;i<zombie_count;i++){
                zombies[i].life = zombies[i].life - board[i][j].power_up;
                if(zombies[i].life <=0 ) {
                    std::cout << "\nZombie " << i << " died\n";
                    zombies[i].row_no = -1;
                    zombies[i].col_no = -1;
                    zombies[i].life = 0;
                }
            }
        }

        reset_cell(i,j);
        board[i][j].is_alien = true;
        board[i][j].representation = 'A';
        alien.row_no = i;
        alien.col_no = j;
    }

    void Rock(int i, int j) {

        //is_rock() contains the number to which it must be replaced
        SetRandomObject(i,j,board[i][j].is_rock);
        if (board[i][j].representation == 'h') {//found health
            std::cout << "\nAlien finds a health Pack beneath the rock\n";
        }

        else if(board[i][j].representation == 'p') {//found health
            std::cout << "\nAlien finds a pod beneath the rock\n";
        }

        else if(board[i][j].representation == 'u') {//found health
            std::cout << "\nAlien finds a Power up beneath the rock\n";
        }

        else if(board[i][j].arrow) //found arrow
            std::cout << "\nAlien finds an arrow\n";
    }

    void AlienTurnEnd(){
        Pause();
        ClearScreen();
        ResetTrail();
        ShowGameBoard();
        Turn(0);
        alien.attack = 0;
        board[alien.row_no][alien.col_no].is_alien = true;
        std::cout << "Alien Turn Over\n";
        std::cout << "The Trail is reset\n";
        ZombieMove();
    }

    void AlienMove(std::string direction){
        int c, r;
        alien.attack=0;

        while(1){
            if(direction=="right") {
                std::cout << "Alien moves right\n";
                c = alien.col_no + 1;
                r = alien.row_no;
            }

            else if(direction=="down") {
                std::cout << "Alien moves down\n";
                c = alien.col_no;
                r = alien.row_no+1;
            }

            else if(direction=="left") {
                std::cout << "Alien moves left\n";
                c = alien.col_no - 1;
                r = alien.row_no;
            }

            else if(direction=="up") {
                std::cout << "Alien moves up\n";
                c = alien.col_no;
                r = alien.row_no-1;
            }

            if (c >= kColumns || r>=kRows || r<0 || c<0) { //it's a wall
                std::cout << "\nAlien faced a wall\n"; //turn ended
                AlienTurnEnd();
                return;
            }

            else if (board[r][c].representation == 'r') {//found rock
                std::cout << "\nAlien stumbles upon a rock\n";

                //if alien finds a rock replace the rock with some other cell
                Rock(r,c); //turn ended
                AlienTurnEnd();
                return;
            }

            else if(board[r][c].arrow){
                std::cout << "\nAlien finds an arrow\n";
                std::cout << "Alien attack is increased by 20\n";
                alien.attack = alien.attack+20;

                if(board[r][c].representation == 'v') {
                    direction = "down";
                    std::cout << "Alien moves down\n";
                }
                else if(board[r][c].representation == '>') {
                    direction = "right";
                    std::cout << "Alien moves right\n";
                }
                else if(board[r][c].representation == '^') {
                    direction = "up";
                    std::cout << "Alien moves up\n";
                }
                else if(board[r][c].representation == '<') {
                    direction = "left";
                    std::cout << "Alien moves left\n";
                }
                reset_cell(alien.row_no, alien.col_no);
                board[alien.row_no][alien.col_no].representation = '.';
                board[alien.row_no][alien.col_no].is_alien = false;
                alien.row_no = r;
                alien.col_no = c;
                board[r][c].is_alien = true;
                board[r][c].representation = 'A';
            }

            else if(board[r][c].is_zombie){
                Pause();
                for(int i=0;i<zombie_count;i++){
                    if(zombies[i].row_no == r && zombies[i].col_no == c) {
                        std::cout << "Alien hits Zombie\n";
                        std::cout << "Zombie " << i + 1 << " got a damage of " << alien.attack << std::endl;
                        zombies[i].life = zombies[i].life-alien.attack;

                        if(zombies[i].life <= 0){
                            std::cout << "\nZombie " << i+1 << " died\n";
                            zombies[i].row_no = -1;
                            zombies[i].col_no = -1;
                            zombies[i].life = 0;
                            reset_cell(alien.row_no, alien.col_no);
                            board[alien.row_no][alien.col_no].representation = '.';
                            alien.row_no = r;
                            alien.col_no = c;
                            board[r][c].is_alien = true;
                            board[r][c].representation = 'A';
                            Pause();
                        }
                        else {
                            AlienTurnEnd();
                            return;
                        }
                    }
                }
            }

            else {
                reset_cell(alien.row_no, alien.col_no);
                board[alien.row_no][alien.col_no].representation = '.';
                DetectCell(r, c);

            }
            Pause();
            ClearScreen();
            ShowGameBoard();
            Turn(0);
        }
    }

    void SaveGame()
    {
        std::string filename;
        std::fstream file;
        int i, j;

        std::cout << "\nEnter the File Name where you want to save the game: ";
        std::cin >> filename;

        file.open(filename, std::ios::out);

        file << kRows << ' ' << kColumns << '\n';
        file << zombie_count << '\n';
        file << alien.row_no << ' ' << alien.col_no <<  ' ' << alien.life <<  ' ' << alien.attack <<  ' ' << alien.range <<  ' ' << alien.isAlive <<   ' ' << alien.representation;
        file << '\n';
        for(i=0; i < zombie_count; i++) {
            file << zombies[i].row_no << ' ';
            file << zombies[i].col_no << ' ';
            file << zombies[i].life << ' ';
            file << zombies[i].attack << ' ';
            file << zombies[i].range << ' ';
            file << zombies[i].isAlive << ' ';
            file << zombies[i].representation << ' ';
            file << '\n';
        }

        for(i=0; i<kRows; i++){
            for(j=0; j<kColumns; j++){
                file << board[i][j].representation;
            }
            file << '\n';
        }
        file.close();
        std::cout << "\nGame is Saved to " << filename << '\n';
        std::cout << "You can load this game anytime.\n\n";
        Pause();
        std::cin.ignore();
    }

    void LoadGame()
    {
        std::string filename;
        std::fstream file;
        int i, j;
        char object;

        std::cout << "\nEnter the File Name where you saved the Game: ";
        std::cin >> filename;

        file.open(filename, std::ios::in);
        if( file.fail() ){
            std::cout << "\nFile <" << filename << "> does not exist!\nPlease save a game first.\n\n";
            Pause();
            return;
        }
        //Pause();
        DeleteGameBoard();
        //Pause();
        file >> kRows >> kColumns >> zombie_count;
        // assigning the memory
        board = new Cell *[kRows];
        for (i = 0; i < kRows; i++)
            board[i] = new Cell[kColumns];
        zombies = new Character[zombie_count];

        file >> alien.row_no >> alien.col_no >> alien.life >> alien.attack >> alien.range >> alien.isAlive >> alien.representation;
        for(i=0; i < zombie_count; i++) {
            file >> zombies[i].row_no;
            file >> zombies[i].col_no;
            file >> zombies[i].life;
            file >> zombies[i].attack;
            file >> zombies[i].range;
            file >> zombies[i].isAlive;
            file >> zombies[i].representation;
        }
        file.ignore();
        file.ignore();
        for(i = 0; i < kRows; i++){
            for(j = 0; j < kColumns; j++){
                file >> std::noskipws >> object;
                board[i][j].representation = object;
                reset_cell(i, j);
                if (object == '^')
                    board[i][j].arrow = 1;
                else if (object == '>')
                    board[i][j].arrow = 2;
                else if (object == 'v')
                    board[i][j].arrow = 3;
                else if (object == '<')
                    board[i][j].arrow = 4;
                else if(object == 'p')
                    board[i][j].pod = 10;
                else if(object == 'h')
                    board[i][j].is_health = 20;
                else if(object == 'u')
                    board[i][j].power_up = 10;
                else if(object == 'r')
                    board[i][j].is_rock = rand() % 8 + 1;
                else if(object == 'A')
                    board[i][j].is_alien = true;
                else if(object >= '1' && object <= '9')
                    board[i][j].is_zombie = true;
            }
            file.ignore();
        }

        file.close();
        std::cout << "\nGame has been loaded from <" << filename << ">.\nYou can Play Now!\n\n";
        Pause();
    }

    int ClearScreen()
    {
#if defined(_WIN32)
        return std::system("cls");
#elif defined(__linux__) || defined(__APPLE__)
        return std::system("clear");
#endif
    }

    int Pause()
    {
#if defined(_WIN32)
        return std::system("pause");
#elif defined(__linux__) || defined(__APPLE__)
        return std::system(R"(read -p "Press any key to continue . . . " dummy)");
#endif
    }

}
#endif