#ifndef CUSTOMER
#define CUSTOMER

#include <bits/stdc++.h>
#include "Stocks.cpp"

using namespace std;

class Customer{
    string id;
    string name;
    vector<Stocks*> s;

public:
    Customer(string id, string name){
        this->id=id;
        this->name=name;
    }

    string getId() const {
        return id;
    }

    const string &getName() const {
        return name;
    }

    void display(){
        cout  << id << " " << name << endl;
    }

    void print_transactions(){
        cout << "Customer Name: " << name << endl;
        cout << "Items Sold\n";
        int count = 1;
        for(int i=0;i<s.size();i++){
            if(s[i]->getStatus()=='S') {
                cout << "Item Number: " << count++;
                cout << "\nType: " << s[i]->getType();
                cout << "\nYear: " << s[i]->getYear();
                cout << "\nGrade: " << s[i]->getGrade();
            }
        }
        count = 1;
        cout << "Items Bought\n";
        for(int i=0;i<s.size();i++){
            if(s[i]->getStatus()=='B') {
                cout << "Item Number: " << count++;

                cout << "\nType: " << s[i]->getType();
                cout << "\nYear: " << s[i]->getYear();
                cout << "\nGrade: " << s[i]->getGrade();
                cout << '\n';
            }
        }

    }

    void add_inventory(Stocks* stock){
        s.push_back(stock);
    }

};

#endif