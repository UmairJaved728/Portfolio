#ifndef PROJECT__CARD_GAME__CSTUDENT_H
#define PROJECT__CARD_GAME__CSTUDENT_H

#include "CCard.h" // Include the header file for the CCard class

using namespace std;

class CStudent : public CCard {
public:
    CStudent(int type, const string name, int power, int resilience); // Constructor for CStudent class

    int getResilience() override; // Override function to get the resilience of the student card
    void setResilience(int resil) override; // Override function to set the resilience of the student card
    bool attack(CCard *c, vector<CCard *> &cards) override; // Override function to attack a card

protected:
    int resilience; // Resilience of the student card
};

#endif //PROJECT__CARD_GAME__CSTUDENT_H
