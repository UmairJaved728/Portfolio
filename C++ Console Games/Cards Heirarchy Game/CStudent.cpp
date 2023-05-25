//
// Name :
//

#include "CStudent.h"

// Constructor for CStudent class
CStudent::CStudent(int type, const string name, int power, int resilience) : CCard(type, name, power),
                                                                             resilience(resilience) {}

// Get method for resilience attribute
int CStudent::getResilience() {
    return resilience;
}

// Set method for resilience attribute
void CStudent::setResilience(int resil) {
    this->resilience = resil;
}

// Method to simulate an attack by the current card
bool CStudent::attack(CCard *c, vector<CCard *> &cards) {
    // Check if there are any cards to attack
    if(cards.empty())
        return false;

    // Choose a random card to attack
    int index = rand() % (cards.size());

    // Calculate the remaining resilience of the attacked card after the attack
    int r = cards[index]->getResilience() - c->getPower();

    // Output the result of the attack
    cout << c->getName() << " attacks " << cards[index]->getName() << ". ";

    // If the attacked card is still alive, update its resilience
    if( r > 0 ) {
        cout << cards[index]->getName() << " 's resilience is now " << r << ".\n";
        cards[index]->setResilience(r);
    }
        // If the attacked card is defeated, remove it from the vector of cards and delete it
    else {
        cards[index]->setResilience(0);
        cout << cards[index]->getName() << " is defeated.\n";
        CCard* c1 = cards[index];
        cards.erase(cards.begin() + index);
        delete c1;
    }
    return true;
}
