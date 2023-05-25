#ifndef SPORTSCARDS
#define SPORTSCARDS

#include <bits/stdc++.h>
#include "Stocks.cpp"

using namespace std;

class SportsCards: public Stocks{
    string player;
    string manufacturer;

public:
    SportsCards(int inventory_number, char type, int year, string grade, string player, string manufacturer): Stocks(inventory_number, type, year, grade) {
        this->player=player;
        this->manufacturer=manufacturer;
    }

    const string &getPlayer1() const {
        return player;
    }

    const string &getManufacturer1() const {
        return manufacturer;
    }

    void display() override{
        Stocks::display();
        cout << "Player " << player;
        cout << "\nManufacturer: " << manufacturer << endl;
    }

    int compare(Stocks* s) override
    {
        if( player > s->getPlayer() )
            return 1;
        else if( player < s->getPlayer() )
            return -1;

        if( manufacturer > s->getManufacturer() )
            return 1;
        else if( manufacturer < s->getManufacturer() )
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