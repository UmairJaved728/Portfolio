#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CCard.h"

using namespace std;

// Class declaration for Player
class Player{
    string name;
    int prestige;
    vector<CCard*> deck;
    vector<CCard*> hand;
    vector<CCard*> table;
public:
    // Constructor to create a new player with the given name
    explicit Player(const char* name);

    // Function to get the name of the player
    const string &getName() const;

    // Function to get the current prestige of the player
    int getPrestige() const;

    // Function to add a card to the deck of the player
    void addCardToDeck(CCard *c);

    // Function to get the top card from the deck of the player
    CCard * getTopCard();

    // Function to add a card to the hand of the player
    void addToHand(CCard *c);

    // Function to get a random card from the hand of the player
    CCard * getRandomCardFromHand();

    // Function to add a card to the table of the player
    void addToTable(CCard *c);

    // Function to reduce the prestige of the player by the given amount
    void reducePrestige(int d);

    // Function to display the cards on the table of the player
    void displayTable();

    // Function to get a reference to the table of the player
    vector<CCard *> & getTable();

    // Function to attack the enemy player with a random card from the table
    void attackPlayer(Player *enemy);

    // Destructor for Player class
    ~Player();
};

#endif //PLAYER_H
