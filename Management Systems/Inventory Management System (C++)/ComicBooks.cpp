#ifndef COMICBOOKS
#define COMICBOOKS

#include <bits/stdc++.h>
#include "Stocks.cpp"

using namespace std;

class ComicBooks: public Stocks{
    string title;
    string publisher;

public:
    ComicBooks(int inventory_number, char type, int year, string grade, string title, string publisher): Stocks(inventory_number, type, year, grade) {
        this->title=title;
        this->publisher=publisher;
    }

    void display() override{
        Stocks::display();
        cout << "\nTitle: " << title;
        cout  << "\nPublisher " << publisher << endl;
    }

    const string &getTitle1() const {
        return title;
    }

    const string &getPublisher1() const {
        return publisher;
    }

    int compare(Stocks* s) override
    {
        if( publisher > s->getPublisher() )
            return 1;
        else if( publisher < s->getPublisher() )
            return -1;

        if( title > s->getTitle() )
            return 1;
        else if( title < s->getTitle() )
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