// CCourseAccreditation class: represents a course accreditation card that can attack other cards
//
// Inherits from:
// - CAdmin class
//
// Attributes:
// - type (int): the type of card (e.g., 1 for monster, 2 for spell, etc.)
// - name (string): the name of the card
// - power (int): the power level of the card
//
// Methods:
// - CCourseAccreditation(int type, const string &name, int power): constructor for CCourseAccreditation object
// - int getPower() override: method that returns the power level of the card
// - bool attack(CCard *c, vector<CCard *> &cards) override: method that allows CCourseAccreditation to attack another card

#ifndef __CCOURSEACCREDITATION_H__
#define __CCOURSEACCREDITATION_H__

#include "CAdmin.h"

using namespace std;

// Constructor for CCourseAccreditation object
class CCourseAcceriditation : public CAdmin{
public:
    CCourseAcceriditation(int type, const string &name, int power);

    // Method that returns the power level of the card
    int getPower() override;

    // Method that allows CCourseAccreditation to attack another card
    bool attack(CCard *c, vector<CCard *> &cards) override;
};

#endif //__CCOURSEACCREDITATION_H__
