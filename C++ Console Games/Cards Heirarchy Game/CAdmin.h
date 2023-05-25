// This is the header file for the CAdmin class which inherits from CCard
// It defines the class interface and member variables and functions

#ifndef PROJECT__CARD_GAME__CADMIN_H
#define PROJECT__CARD_GAME__CADMIN_H

#include "CCard.h" // include the header file for the base class CCard

using namespace std;

class CAdmin : public CCard{
public:
// Constructor to initialize the object with a given type, name and power
    CAdmin(int type, const string name, int power);

// Attack function that overrides the virtual function in the base class CCard
// It takes a pointer to another CCard object and a reference to a vector of CCard pointers
// It returns a boolean value indicating the result of the attack
    bool attack(CCard *c, vector<CCard *> &cards) override;
};

#endif //PROJECT__CARD_GAME__CADMIN_H