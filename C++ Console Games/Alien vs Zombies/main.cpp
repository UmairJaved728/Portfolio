//main
// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TxxL
// Names: MEMBER_NAME_1 | MEMBER_NAME_2 | MEMBER_NAME_3
// IDs: MEMBER_ID_1 | MEMBER_ID_2 | MEMBER_ID_3
// Emails: MEMBER_EMAIL_1 | MEMBER_EMAIL_2 | MEMBER_EMAIL_3
// Phones: MEMBER_PHONE_1 | MEMBER_PHONE_2 | MEMBER_PHONE_3
// *********************************************************

// TODO: Fill in the missing information above and delete this line.

#include "helper.cpp"
#include <iostream>
#include <string>

using namespace std;

void Caps_to_small(string &a);

int main()
{
    char isPlay = true, choice;
    string input;
    int over;
    srand(time(0));

    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl << endl;

    do{
        pf::PrintGameSettings();
        do{
            std::cout << "\nDo you wish to change the game settings (y/n)? => ";
            cin >> choice;
            choice |= 32;
            if(choice == 'y')
                pf::ChangeGameSettings();
            else if(choice == 'n')
                break;
            else
                std::cout << "\nInvalid Input!\n";
        }while( !(choice == 'n' || choice == 'y') );

        pf::CreateGameBoard();

        cin.ignore();

        over = 0;
        while( !over )
        {
            over = pf::GameOver();
            if(over == 1){
                std::cout << "\n\n" << "Congratulations!! Alien Wins.\n\n";
                pf::Pause();
                break;
            } else if(over == 2){
                std::cout << "\n\n" << "Alien Lost!!.\n\n";
                pf::Pause();
                break;
            }
            pf::ClearScreen();
            pf::ShowGameBoard();
            pf::Turn(0);
            cout << "\nCommand> ";
            getline(cin, input, '\n');
            Caps_to_small(input);

            if(input=="up") {
                pf::AlienMove(input);
            }
            else if(input=="down") {
                pf::AlienMove(input);
            }
            else if(input=="left") {
                pf::AlienMove(input);
            }
            else if(input=="right") {
                pf::AlienMove(input);
            }
            else if(input=="arrow") {
                pf::ChangeArrow();
            }
            else if(input=="help") {
                pf::Help();
            }
            else if(input=="save") {
                pf::SaveGame();
            }
            else if(input=="load") {
                pf::LoadGame();
            }
            else if(input=="quit") {
                cout << "\nAre you sure? (y/n) : ";
                cin >> choice;
                std::cin.ignore();
                choice |= 32;
                if(choice == 'y') {
                    cout << "Goodbye!\n";
                    break;
                }
                else
                    cout << "Aborting...\n";
                pf::Pause();
            }
            else {
                cout << "\nInvalid Input!\n\n";
                pf::Pause();
            }
        }

        pf::DeleteGameBoard();
        cout << "\nDo you want to Play Again? (y/n) : ";
        cin >> choice;

        choice |= 32;

        if(choice == 'y')
            isPlay = true;
        else
            isPlay = false;

    }while( isPlay );
    return 0;
}

void Caps_to_small(string &a){
    for(int i=0;i<a.size();i++){
        if(a[i]>=65 && a[i]<=90)
            a=a[i]+32;
    }
}







/*
 for(int r=0;r<pf::kRows;r++){
    for(int c=0;c<pf::kColumns;c++){
        if(pf::board[r][c].is_zombie){
            for(int i=0;i<pf::zombie_count;i++){
                if(pf::zombies[i].row_no == r && pf::zombies[i].col_no == c) {
                    cout << pf::zombies[i].row_no << " " << pf::zombies[i].col_no;
                    std::cout << "Alien hits Zombie\n";
                    std::cout << "Zombie " << i + 1 << "got a damage of " << pf::alien.attack << std::endl;
                    pf::zombies[i].life = pf::zombies[i].life-pf::alien.attack;
                }
            }
        }
    }


    for(int i=0;i<pf::zombie_count;i++){
    cout << pf::zombies[i].row_no << " col " << pf::zombies[i].col_no;
}
}*/