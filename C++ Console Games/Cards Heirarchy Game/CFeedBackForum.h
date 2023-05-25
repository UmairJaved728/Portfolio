// CFeedbackForum class implementation: represents a feedback forum card that can boost the power of other cards
//
// Inherits from:
// - CAdmin class
//
// Fields:
// - boost: an integer representing the boost amount
//
// Methods:
// - CFeedbackForum(int type, const string name, int power, int boost): constructor for CFeedbackForum object
// - int getBoost() override: method that returns the boost amount of the card
// - bool attack(CCard *c, vector<CCard *> &cards) override: method that allows CFeedbackForum to boost another card's power

#ifndef PROJECT__CARD_GAME__CFEEDBACKFORUM_H
#define PROJECT__CARD_GAME__CFEEDBACKFORUM_H

#include "CAdmin.h"

using namespace std;

class CFeedbackForum : public CAdmin{
private:
    int boost;
public:
    // Constructor for CFeedbackForum object
    CFeedbackForum(int type, const string name, int power, int boost);

    // Method that returns the boost amount of the card
    int getBoost() override;

    // Method that allows CFeedbackForum to boost another card's power
    bool attack(CCard *c, vector<CCard *> &cards) override;
};

#endif //PROJECT__CARD_GAME__CFEEDBACKFORUM_H
