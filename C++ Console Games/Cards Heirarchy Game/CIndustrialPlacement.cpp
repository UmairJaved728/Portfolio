// Implementation of CIndustrialPlacement class, which is a derived class of CStudent
// It represents a specific type of student card called "Industrial Placement"
// This class adds a boost to the resilience of the student when getBoost() method is called
// Inherits the attack() method from its parent class, CStudent

#include "CIndustrialPlacement.h"

// Constructor
// Initializes the object with the given type, name, power, resilience and boost values
CIndustrialPlacement::CIndustrialPlacement(int type, const string &name, int power, int resilience, int boost) : CStudent(type, name, power, resilience),
                                                                                                                 boost(boost) {}

// Returns the boost value of the card
// Adds the boost value to the resilience of the card
int CIndustrialPlacement::getBoost() {
    CStudent::resilience += boost;
    return 0;
}

// Overrides the attack() method of its parent class
// Calls the getBoost() method of the card being attacked to increase resilience
// Then calls the attack() method of its parent class to carry out the attack
bool CIndustrialPlacement::attack(CCard *c, vector<CCard *> &cards) {
    c->getBoost();
    return CStudent::attack(c, cards);
}