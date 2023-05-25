// CAdmin class: represents an administrative card that can attack other cards
//
// Attributes:
// - type (int): the type of card (e.g., 1 for monster, 2 for spell, etc.)
// - name (string): the name of the card
// - power (int): the power level of the card
//
// Methods:
// - CAdmin(int type, const string name, int power): constructor for CAdmin object
// - bool attack(CCard *c, vector<CCard *> &cards): method that allows CAdmin to attack another card
// - bool attack(CCard* c, vector<CCard*>& cards): helper method that handles attack logic

#include "CAdmin.h"

// Constructor for CAdmin object
CAdmin::CAdmin(int type, const string name, int power) : CCard(type, name, power) {}

// Method that allows CAdmin to attack another card
bool CAdmin::attack(CCard *c, vector<CCard *> &cards) {
    return CCard::attack(c, cards);
}

// Helper method that handles attack logic
bool attack(CCard* c, vector<CCard*>& cards)  { return false; }
