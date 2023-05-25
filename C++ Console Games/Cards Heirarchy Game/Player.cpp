// This is the implementation file for the Player class.
// It defines the methods for the Player class.

#include "Player.h"

// Returns the name of the player.
const string &Player::getName() const {
    return name;
}

// Returns the current prestige of the player.
int Player::getPrestige() const {
    return prestige;
}

// Constructs a player with the given name and default prestige of 30.
Player::Player(const char* name)
{
    this->name = name;
    prestige = 30;
    hand.push_back(nullptr);
    hand.push_back(nullptr);
}

// Adds a card to the player's deck.
void Player::addCardToDeck(CCard *c){
    deck.push_back(c);
}

// Removes and returns the top card from the player's deck.
CCard * Player::getTopCard(){
    if(deck.empty())
        return nullptr;
    CCard* c = deck[0];
    deck.erase(deck.begin());
    return c;
}

// Adds a card to the player's hand.
void Player::addToHand(CCard *c){
    if(hand[0] == nullptr)
        hand[0] = c;
    else
        hand[1] = c;
}

// Removes and returns a random card from the player's hand.
CCard * Player::getRandomCardFromHand(){
    int random = rand() % (2);
    CCard* c = hand[random];
    hand[random] = nullptr;
    return c;
}

// Adds a card to the player's table.
void Player::addToTable(CCard *c){
    table.push_back(c);
}

// Displays the cards on the player's table.
void Player::displayTable(){
    cout << "Cards on table:";
    for(vector<CCard*>::reverse_iterator i = table.rbegin(); i != table.rend(); i++)
        cout << " " << (*i)->getName() << " (" << (*i)->getResilience() << "),";
    cout << '\n';
}

// Returns a reference to the vector of cards on the player's table.
vector<CCard *> & Player::getTable() {
    return table;
}

// Reduces the player's prestige by the given amount.
void Player::reducePrestige(int d)
{
    prestige -= d;
}

// Attacks the given enemy player using cards on the player's table.
void Player::attackPlayer(Player *enemy)
{
    for(vector<CCard*>::reverse_iterator i = table.rbegin(); i != table.rend(); i++) {
        if ( !(*i)->attack((*i), enemy->table) )
        {
            int r = enemy->prestige - (*i)->getPower();
            cout << (*i)->getName() << " attacks " << enemy->getName() << ". ";
            cout << enemy->name << "'s prestige is now ";
            if(r < 0)
                cout << "0";
            else
                cout << r;
            cout << ".\n";
            enemy->prestige = (r < 0) ? 0 : r ;
        }
    }
}

// Destructor for the Player class. Deletes all cards in the player's deck, hand, and table.
Player::~Player(){
    for(auto &c : deck)
        delete c;
    deck.clear();
    for(auto &c : hand)
        delete c;
    hand.clear();
    for(auto &c : table)
        delete c;
    table.clear();
}