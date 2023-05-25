#include<iostream>
#include<cstring>
#include "Game.h"

using namespace std;

int main()
{
    // This constant represents the number of rounds in the game.
    const int ROUNDS = 30;

    // These variables keep track of the current round number and the random seed.
    int count, s;

    // A Game object is created to manage the game.
    Game game;

    // This code reads the random seed from a file called "seed.txt".
    ifstream seed("seed.txt");

    if(seed.fail())
        s = 0;
    else
    {
        seed >> s;
        seed.close();
    }

    // The random number generator is seeded using the srand function.
    srand(time((time_t*)&s));

    // This message is displayed at the start of the game.
    cout << "Welcome to U-Can't. Let the winnowing begin...\n\n";

    // The names of the two players and their data files are added to the game object.
    game.addPlayer("Professor Plagiarist", "plagiarist.txt");
    game.addPlayer("Professor Piffle-Paper", "piffle-paper.txt");

    // This loop runs for ROUNDS iterations, playing a round of the game in each iteration.
    for(count = 1; count <= ROUNDS; count++)
    {
        // This message displays the current round number.
        cout << "\nRound " << count << '\n';
        // Play this round for all players
        game.playRound();
        // check if game ended then stop rounds
        if(game.isWin())
            break;
    }
    // show the results and winner
    game.showResults();
    return 0;
}

/*
 To compile : g++ CCard.cpp CCourseAccreditation.cpp CFeedBackForum.cpp CIndustrialPlacement.cpp CplagirarismHearing.cpp CStudent.cpp CAdmin.cpp Game.cpp Player.cpp main.cpp -o main
 To Run : ./main
 */