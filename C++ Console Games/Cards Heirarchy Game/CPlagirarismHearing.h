// Name: CPlagiarismHearing.h
// This is the header file for the CPlagiarismHearing class.

#ifndef PROJECT__CARD_GAME__CPLAGIRARISMHEARING_H
#define PROJECT__CARD_GAME__CPLAGIRARISMHEARING_H

#include "CAdmin.h"

using namespace std;

class CPlagiarismHearing : public CAdmin{
public:
    // Constructor for the CPlagiarismHearing class. Initializes the type, name, and power of the hearing.
    CPlagiarismHearing(int type, const string name, int power);

    // Overrides the getPower() function of the base class to return the power of the hearing.
    int getPower() override;

    // Overrides the attack() function of the base class to attack a card from the provided vector.
    // Returns true if an attack is made successfully, false otherwise.
    bool attack(CCard *c, vector<CCard *> &cards) override;
};

#endif //PROJECT__CARD_GAME__CPLAGIRARISMHEARING_H
