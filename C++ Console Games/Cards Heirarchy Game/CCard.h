#ifndef CCARD_H
#define CCARD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector> // Include vector header file for using vector data type

using namespace std;

class CCard; // Declare the class

class CCard {
protected:
    int type; // Type of card (Admin, Student)
    string name; // Name of the card
    int power; // Power level of the card

public:
    CCard(int type, string name, int power); // Constructor for CCard class

    const string &getName() const; // Function to get the name of the card
    int getType() const; // Function to get the type of the card
    virtual int getPower(); // Virtual function to get the power of the card
    virtual int getResilience(); // Virtual function to get the resilience of the card
    virtual void setResilience(int resilience); // Virtual function to set the resilience of the card
    virtual int getBoost(); // Virtual function to get the boost of the card
    virtual bool attack(CCard *c, vector<CCard *> &cards); // Virtual function to attack a card
};

#endif
