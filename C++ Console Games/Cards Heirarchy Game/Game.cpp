//
// Name :
//

#include "Game.h"

void Game::addPlayer(const char* name, const char* filename){

    // Create a new player with the given name
    auto p = new Player(name);

    // Open the file with the given filename
    fstream file(filename, ios::in);
    if( file.fail() )
        return;

    // Initialize variables for reading from file
    string line;
    istringstream ss;
    int type;
    string label, temp;
    int power, boost, resilience;
    CCard* card;

    // Loop through each line in the file
    while( getline(file, line) )
    {
        // Clear the string stream and set the string stream to the current line
        ss.clear();
        ss.str(line);

        // Read in the type, label, power, and any additional variables based on the type
        ss >> type;
        ss >> label;
        ss >> temp;
        label.append(" ");
        label.append(temp);
        ss >> power;
        if(type == 1) {
            ss >> resilience;
            card = new CStudent(type,label, power, resilience);
        }
        else if(type == 2)
            card = new CPlagiarismHearing(type, label, power);
        else if(type == 3)
            card = new CCourseAcceriditation(type, label, power);
        else if(type == 4) {
            ss >> boost;
            card = new CFeedbackForum(type, label, power, boost);
        }
        else if(type == 5){
            ss >> resilience >> boost;
            card = new CIndustrialPlacement(type, label, power, resilience, boost);
        } else {
            card = new CCard(type, label, power);
        }

        // Add the new card to the player's deck
        p->addCardToDeck(card);
    }

    // Close the file
    file.close();

    // Draw the top card from the player's deck and add it to their hand
    card = p->getTopCard();
    p->addToHand(card);

    // Add the player to the list of players in the game
    players.push_back(p);

    // Print a message indicating that the player has been added and what card they start with
    cout << p->getName() << " starts with " << card->getName() << '\n';
}

/**
 * This function searches through the players vector to find the index of the given player.
 * @param h A pointer to the player to search for.
 * @return The index of the player in the players vector, or -1 if the player was not found.
 */
int Game::getIndexOfPlayer(Player* h)
{
    for(int i=0; i<players.size(); i++)
        if(h->getName() == players[i]->getName())
            return i;
    return -1;
}

/**
 * This function checks whether any players have a prestige greater than zero.
 * @return True if there is only one player left with a prestige greater than zero, false otherwise.
 */
bool Game::isWin()
{
    int count = 0;
    for(auto& p : players)
        if(p->getPrestige() > 0)
            count++;
    if(count == 1)
        return true;
    return false;
}

/**
 * This function displays the final results of the game, including each player's final prestige and
 * the name of the winning player.
 */
void Game::showResults()
{
    int max = 0;
    string winner = "Winner";
    cout << "\nGame over\n\n";
    for(auto & p : players){
        cout << p->getName() << " prestige is " << ((p->getPrestige() < 0) ? 0 : p->getPrestige()) << '\n';
        if (max < p->getPrestige())
        {
            max = p->getPrestige();
            winner = p->getName();
        }
    }

    cout << '\n' << winner << " wins!\n";

    for(auto p : players) {
        delete p;
    }

    players.clear();
}

// This function plays a round of the game for all the players
void Game::playRound() {
// Declare a CCard pointer and an integer index to keep track of the current player
    CCard *c;
    int index = 0;
// Iterate over all the players
    for (auto p: players) {
// Increment the index and skip the current player if their prestige is zero or negative
        index++;
        if (p->getPrestige() <= 0)
            continue;
// Get the top card from the player's deck and skip the current player if their deck is empty
        c = p->getTopCard();
        if (c == nullptr) {
            cout << p->getName() << " is out of deck and so sacked!" << '\n';
            continue;
        }
// Print the name of the player and the name of the card they drew
        cout << p->getName() << " draws " << c->getName() << '\n';
// Add the card to the player's hand
        p->addToHand(c);
// Get a random card from the player's hand and print the name of the player and the name of the card they played
        c = p->getRandomCardFromHand();
        cout << p->getName() << " plays " << c->getName() << '\n';
// Add the card to the player's table if it is a character or an artifact card
        if (c->getType() == 1 || c->getType() == 5)
            p->addToTable(c);
// Display the player's table
        p->displayTable();
        // card is of type 4, special behaviour
        if (c->getType() == 4) {
            // Choose a random player
            int r = rand() % (players.size());
            // If the chosen player is the current player, the friendly professor card helps the current player
            if (r == getIndexOfPlayer(p)) {
                cout << "Friendly Professor is chosen.\n";
                cout << c->getName() << " helps " << p->getName() << ". ";
                // Increase the current player's prestige by the boost value of the card
                p->reducePrestige(-c->getBoost());
                cout << p->getName() << "'s prestige is now " << p->getPrestige() << "\n";
            }
                // If the chosen player is not the current player, the card attacks the chosen player
            else {
                // Attack the chosen player's table with the card and decrease their prestige by the power value of the card
                if (!c->attack(c, players[r]->getTable())) {
                    players[r]->reducePrestige(c->getPower());
                    // Print the name of the card, the name of the attacked player and their updated prestige
                    cout << c->getName() << " attacks " << players[r]->getName() << ". ";
                    cout << players[r]->getName() << "'s prestige is now ";
                    r = players[r]->getPrestige();
                    if (r < 0)
                        cout << "0";
                    else
                        cout << r;
                    cout << ".\n";
                }
            }
        }
            // If the card is not a professor card, attack all other players except the current player with the card
        else {
            for (int i = 0; i < players.size(); i++) {
                Player *enemy = players[i];
                // Skip the current player and any player with zero or negative prestige
                if (enemy->getName() == p->getName() || enemy->getPrestige() <= 0)
                    continue;
                // If the card is a character or an artifact card, attack the enemy player's table
                if (c->getType() == 1 || c->getType() == 5 || c->getType() == 3)
                    p->attackPlayer(enemy);
                    // If the card is a trap card, choose a random player (except the current player) and either attack the chosen player or attack the enemy player's table
                else if (c->getType() == 2) {
                    int r = rand() % (players.size() + 1);
                    while (r == index)
                        r = rand() % (players.size() + 1);
                    // If the random player is equal to the total number of players, attack the enemy player's prestige directly
                    if (r == players.size()) {
                        enemy->reducePrestige(c->getPower());
                        r = enemy->getPrestige();
                        // Print the name of the card, the name of the attacked player and their updated prestige
                        cout << c->getName() << " attacks " << enemy->getName() << ". ";
                        cout << enemy->getName() << "'s prestige is now ";
                        if (r < 0)
                            cout << "0";
                        else
                            cout << r;
                        cout << ".\n";
                    } else
                        c->attack(c, enemy->getTable());
                } else
                    c->attack(c, enemy->getTable());

                // If the enemy player's prestige is zero or negative, print a message that they are sacked
                if (enemy->getPrestige() <= 0) {
                    cout << enemy->getName() << " has no prestige and is sacked!\n";
                }
            }
        }
    }
}
