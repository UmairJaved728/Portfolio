#ifndef STOCKS
#define STOCKS

#include <bits/stdc++.h>

using namespace std;

class Stocks{
    int inventory_number;
    char type;
    int year;
    string grade;
    char status; //whether the item is bought or sell

public:
    Stocks(int inventory_number, char type, int year, string grade) {
        this->inventory_number=inventory_number;
        this->type=type;
        this->year=year;
        this->grade=grade;
        status = 'N';
    }

    int getInventoryNumber() const {
        return inventory_number;
    }

    virtual void display(){
        cout << "Number of item in inventory: " << inventory_number;
        cout << "\nType: " << type;
        cout << "\nYear: " << year;
        cout << "\nGrade: " << grade;
    }

    void set_status(char c)
    {
        status = c;
    }

    char getType() const {
        return type;
    }

    virtual string getTitle() const {
        return "";
    }

    virtual string getPublisher() const {
        return "";
    }

    virtual string getCoinType() {
        return "";
    }

    virtual string getPlayer() const {
        return "";
    }

    virtual string getManufacturer() const {
        return "";
    }

    int getYear() const {
        return year;
    }

    const string &getGrade() const {
        return grade;
    }

    char getStatus() const {
        return status;
    }

    virtual int compare(Stocks* s) = 0;
};

#endif