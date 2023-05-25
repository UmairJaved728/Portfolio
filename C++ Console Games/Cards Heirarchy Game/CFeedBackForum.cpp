// Name: CFeedBackForum.cpp
// This is the implementation file for the CFeedbackForum class.

#include "CFeedBackForum.h"

// Constructor for the CFeedbackForum class. Initializes the type, name, power, and boost of the forum.
CFeedbackForum::CFeedbackForum(int type, const string name, int power, int boost) : CAdmin(type, name, power), boost(boost) {}

// Returns the boost value of the forum.
int CFeedbackForum::getBoost() {
    return boost;
}

// Attacks a card from the provided vector. Returns true if an attack is made successfully, false otherwise.
bool CFeedbackForum::attack(CCard *c, vector<CCard *> &cards) {
    if(cards.empty())
        return false;

    // Randomly select a card from the provided vector.
    int index = rand() % (cards.size());
    int r = cards[index]->getResilience() - c->getPower();

    // Print out the chosen card and the attack details.
    cout << "The chosen Card is " << cards[index]->getName() << ".\n";
    cout << c->getName() << " attacks " << cards[index]->getName() << ". ";

    // If the attacked card's resilience is greater than the attacking card's power, reduce the resilience.
    if( r > 0 ) {
        cout << cards[index]->getName() << "'s resilience is now " << r << ".\n";
        cards[index]->setResilience(r);
    }
        // If the attacked card's resilience is less than or equal to the attacking card's power, defeat the card.
    else {
        cards[index]->setResilience(0);
        cout << cards[index]->getName() << " is defeated.\n";

        // Remove the defeated card from the vector and free its memory.
        CCard* c1 = cards[index];
        cards.erase(cards.begin() + index);
        delete c1;
    }
    return true;
}
