#ifndef COIN
#define COIN

#include <bits/stdc++.h>
#include "Stocks.cpp"

using namespace std;

class Coin: public Stocks{
    string coinType;
public:
    const string &getTitle1() const {
        return coinType;
    }

public:
    Coin(int inventory_number, char type, int year, string grade, string cType): Stocks(inventory_number, type, year, grade) {
        this->coinType=cType;
    }

    void display() override{
        Stocks::display();
        cout << "\nCoin Type: ";
        cout << coinType << endl;
    }

    string getCoinType() override {
        return coinType;
    }

    int compare(Stocks* s) override
    {
        if( coinType > s->getCoinType() )
            return 1;
        else if( coinType < s->getCoinType() )
            return -1;

        if( getYear() > s->getYear() )
            return 1;
        else if( getYear() < s->getYear() )
            return -1;

        if( getGrade() > s->getGrade() )
            return 1;
        else if( getGrade() < s->getGrade() )
            return -1;

        return 0;
    }
};

#endif