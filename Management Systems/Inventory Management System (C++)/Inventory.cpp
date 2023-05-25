#ifndef INVENTORY
#define INVENTORY

#include <bits/stdc++.h>
#include "Coins.cpp"
#include "ComicBooks.cpp"
#include "SportsCards.cpp"
#include "BSTInventory.cpp"

using namespace std;

class Inventory{
    SearchTree sTree;
public:
    Inventory(){
        fstream inventory;
        inventory.open("inventory_list.txt", ios::in);
        if(inventory.fail()) { //if file does not open for certain reasons
            cout << "\n\t\t\t\t\t\tFile cannot be open. Terminating Program......" << endl;
            exit(1);
        }

        //Data Reading
        while (!inventory.eof()){
            char type_of_item;
            char comma;
            inventory >> type_of_item;
            inventory >> comma;

            if (type_of_item == 'M') { //reading and object creation
                int number_in_inventory;
                int year;
                string grade;
                string title;

                inventory >> number_in_inventory;
                inventory >> comma;
                inventory >> year;
                inventory >> comma;
                getline(inventory, grade, '\n');
                getline(inventory, title, '\n');
                //cout << type_of_item << ' ' << number_in_inventory << ' ' << year << ' ' << grade << ' ' << coinType << endl;
                Stocks *coin = new Coin(number_in_inventory, type_of_item, year, grade, title);
                sTree.insert(coin);
            }

            else if (type_of_item == 'C') { //reading and object creation
                int number_in_inventory;
                int year;
                string grade;
                string title;
                string publisher;

                inventory >> number_in_inventory;
                inventory >> comma;
                inventory >> year;
                inventory >> comma;
                getline(inventory, grade, ',');
                getline(inventory, title, ',');
                getline(inventory, publisher, '\n');
                //cout << type_of_item << ' ' << number_in_inventory << ' ' << year << ' ' << grade << ' ' << coinType << ' ' << publisher << endl;
                Stocks *comic = new ComicBooks(number_in_inventory, type_of_item, year, grade, title, publisher);
                sTree.insert(comic);
            }

            else if (type_of_item == 'S') { //reading and object creation
                int number_in_inventory;
                int year;
                string grade;
                string player;
                string manufacturer;

                inventory >> number_in_inventory;
                inventory >> comma;
                inventory >> year;
                inventory >> comma;
                getline(inventory, grade, ',');
                getline(inventory, player, ',');
                getline(inventory, manufacturer, '\n');
                //cout << type_of_item << ' ' << number_in_inventory << ' ' << year << ' ' << grade << ' ' << player << ' ' << manufacturer << endl;
                Stocks* sports = new SportsCards(number_in_inventory, type_of_item, year, grade, player, manufacturer);
                sTree.insert(sports);
            }
            else { //invalid entry only reading
                int number_in_inventory;
                int year;
                string grade;
                string player;
                string manufacturer;

                inventory >> number_in_inventory;
                inventory >> comma;
                inventory >> year;
                inventory >> comma;
                getline(inventory, grade, ',');
                getline(inventory, player, ',');
                getline(inventory, manufacturer, '\n');
            }
        }
        inventory.close();
    }

    void display()
    {
        cout << "Inventory Items:\n\n";
        cout << "Number of Items in inventory:\n";
        cout << "Coins: " << sTree.count('M') << '\n';
        cout << "Comic Books: " << sTree.count('C') << '\n';
        cout << "Sports Cards: " << sTree.count('S') << '\n';
        sTree.traverse();
    }

    void remove(Stocks* s){
        sTree.remove(s);
    }

    void insert(Stocks* s)
    {
        sTree.insert(s);
    }
};

#endif