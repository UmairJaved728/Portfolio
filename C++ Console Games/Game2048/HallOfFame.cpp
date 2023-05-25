//
// Created on 12/30/2022.
//

#include<iostream>
#include<iomanip>
#include<fstream>
#include "HallOfFame.h"

using namespace std;

HallOfFame::HallOfFame()
{
    capacity = 20;
    size = 0;

    records = new Record[capacity];
}

void HallOfFame::loadData()
{
    string name;
    char t;
    fstream file;

    file.open(HALL_OF_FAME_FILENAME, ios::in);

    if(file.fail())
        return;
    getline(file, name, ':');
    while( !name.empty() )
    {
        if(size == capacity)
            resize();

        records[size].name = name;
        file >> records[size].points;
        size++;
        file.ignore();
        getline(file, name, ':');

        if(file.fail())
            break;
    }

    file.close();
    sortHallOfFame();
}
void HallOfFame::addRecord(int points)
{
    string name;
    fstream file;
    file.open(HALL_OF_FAME_FILENAME, ios::app);
    cout << "Now we need your Name as a record of our Hall Of Fame.\n";
    cin.ignore();
    cout << "Please enter your Name: ";
    getline(cin, name, '\n');
    file << name << ":" << points << '\n';
    file.close();

    if(size == capacity)
        resize();

    records[size].name = name;
    records[size].points = points;
    size++;
}

void HallOfFame::sortHallOfFame() {
    int i, j;
    Record key;
    for (i = 1; i < size; i++)
    {
        key.name = records[i].name;
        key.points = records[i].points;
        j = i - 1;

        while (j >= 0 && records[j].points < key.points)
        {
            records[j + 1].name = records[j].name;
            records[j + 1].points = records[j].points;
            j = j - 1;
        }
        records[j + 1].name = key.name;
        records[j + 1].points = key.points;
    }
}

void HallOfFame::printHallOfFame()
{
    int i;
    sortHallOfFame();
    cout << "\n\t\t\tHall of Fame of 2048 Game,\n\n";
    if(size == 0)
        cout << "OOPS! Hall of Fame is currently empty.\nCan you Win? (^,^)\n\n";
    else{
        cout << "|           Player's Name             |            Points            |\n";
        cout << "|-------------------------------------|------------------------------|\n";
    }
    for(i=0; i<size; i++)
    {
        cout  << "|        " << fixed << setw(15) << records[i].name << "              ";
        cout << "|";
        cout << "       " << fixed << setw(10) << records[i].points << "             |";
        cout << "\n";
    }
    cout << "\n";
    system("pause");
}

HallOfFame::~HallOfFame() {
    delete[] records;
}