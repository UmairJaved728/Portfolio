// Name: CPlagirarismHearing.cpp
// This is the implementation file for the CPlagiarismHearing class.

#include "CPlagirarismHearing.h"

CPlagiarismHearing::CPlagiarismHearing(int type, const string name, int power) : CAdmin(type, name, power) {}

int CPlagiarismHearing::getPower() {
    // Returns the power of the hearing.
    return power;
}

bool CPlagiarismHearing::attack(CCard *c, vector<CCard *> &cards) {
    if(cards.empty())
        return false;
    int index = rand() % (cards.size());
    int r = cards[index]->getResilience() - c->getPower();

    cout << c->getName() << " attacks " << cards[index]->getName() << ". ";
    if( r > 0 ) {
        // If the attacked card's resilience is greater than zero after the attack, set its new resilience and print a message.
        cout << cards[index]->getName() << " 's resilience is now " << r << ".\n";
        cards[index]->setResilience(r);
    }
    else {
        // If the attacked card's resilience is zero or below, set its resilience to zero, delete the card, and print a message.
        cards[index]->setResilience(0);
        cout << cards[index]->getName() << " is defeated.\n";
        CCard* c1 = cards[index];
        cards.erase(cards.begin() + index);
        delete c1;
    }
    return true;
}
