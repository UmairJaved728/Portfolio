// The following code defines a class called Game which includes several header files for various other classes
// The class Game manages a vector of pointers to Player objects, representing players in the game
// The class has methods for adding a player, getting the index of a player, checking if a player has won,
// displaying the results, and playing a round of the game.

#ifndef GAME_ // Preprocessor directive to ensure the header file is only included once
#define GAME_

#include "Player.h" // Header file for the Player class
#include "CCard.h" // Header file for the CCard class
#include "CAdmin.h" // Header file for the CAdmin class
#include "CStudent.h" // Header file for the CStudent class
#include "CCourseAccreditation.h" // Header file for the CCourseAccreditation class
#include "CFeedBackForum.h" // Header file for the CFeedBackForum class
#include "CIndustrialPlacement.h" // Header file for the CIndustrialPlacement class
#include "CPlagirarismHearing.h" // Header file for the CPlagirarismHearing class

class Game{
    vector<Player*> players; // A vector of pointers to Player objects
public:
    Game() = default; // Default constructor
    void addPlayer(const char* name, const char* filename); // Method for adding a player to the game
    int getIndexOfPlayer(Player* h); // Method for getting the index of a player in the vector
    bool isWin(); // Method for checking if a player has won the game
    void showResults(); // Method for displaying the results of the game
    void playRound(); // Method for playing a round of the game
};

#endif // End of the preprocessor directive