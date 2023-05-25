// CCourseAccreditation class implementation: represents a course accreditation card that can attack other cards
//
// Inherits from:
// - CAdmin class
//
// Methods:
// - CCourseAccreditation(int type, const string &name, int power): constructor for CCourseAccreditation object
// - int getPower() override: method that returns the power level of the card
// - bool attack(CCard *c, vector<CCard *> &cards) override: method that allows CCourseAccreditation to attack another card

#include "CCourseAccreditation.h"

// Constructor for CCourseAccreditation object
CCourseAcceriditation::CCourseAcceriditation(int type, const string &name, int power) : CAdmin(type, name, power) {}

// Method that returns the power level of the card
int CCourseAcceriditation::getPower() {
    return power;
}

// Method that allows CCourseAccreditation to attack another card
bool CCourseAcceriditation::attack(CCard *c, vector<CCard *> &cards){
    if(cards.empty())
        return false;

    for(auto index = 0; index<cards.size(); index++)
    {
        int r = cards[index]->getResilience() - c->getPower();
        cout << c->getName() << " attacks " << cards[index]->getName() << ". ";

        // Check if the attacking card can defeat the other card
        if( r > 0 ) {
            cout << cards[index]->getName() << "'s resilience is now " << r << ".\n";
            cards[index]->setResilience(r);
        }
        else {
            // Defeat the other card and remove it from the vector
            cards[index]->setResilience(0);
            cout << cards[index]->getName() << " is defeated.\n";
            CCard* c1 = cards[index];
            cards.erase(cards.begin() + index);
            delete c1;
        }
    }
    return false;
}
