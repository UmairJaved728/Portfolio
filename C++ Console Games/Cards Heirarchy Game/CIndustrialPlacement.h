#ifndef PROJECT__CARD_GAME__CINDUSTRIALPLACEMENT_H
#define PROJECT__CARD_GAME__CINDUSTRIALPLACEMENT_H

#include "CStudent.h"

using namespace std;

class CIndustrialPlacement : public CStudent{
private:
    int boost;
public:
    // Constructor for CIndustrialPlacement
    CIndustrialPlacement(int type, const string &name, int power, int resilience, int boost);

    // Getter for boost attribute
    int getBoost() override;

    // Attack function for CIndustrialPlacement card
    bool attack(CCard *c, vector<CCard *> &cards) override;
};

#endif //PROJECT__CARD_GAME__CINDUSTRIALPLACEMENT_H
