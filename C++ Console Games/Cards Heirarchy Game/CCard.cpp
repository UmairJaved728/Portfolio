// Include the header file for CCard class
#include "CCard.h"

// Constructor for CCard class
CCard::CCard(int type, string name, int power) : type(type), name(name), power(power) {}

// Function to get the name of the card
const string &CCard::getName() const {
    return name;
}

// Function to get the type of the card
int CCard::getType() const {
    return type;
}

// Function to get the power of the card
int CCard::getPower() {
    return power;
}

// Function to get the resilience of the card
int CCard::getResilience() {
    return 0;
}

// Function to set the resilience of the card
void CCard::setResilience(int resilience) {}

// Function to get the boost of the card
int CCard::getBoost() {
    return 0;
}

// Function to attack a card
bool CCard::attack(CCard *c, vector<CCard *> &cards) {
    // Display a message indicating that the card is of no type and cannot be activated
    cout << c->getName() << " is of no type. " << c->getName() << " cannot be activated.\n";
    return true;
}
