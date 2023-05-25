//
// Created on 12/30/2022.
//

#ifndef PROJECT_2048_GAME__HALLOFFAME_H
#define PROJECT_2048_GAME__HALLOFFAME_H

#include<iostream>

using namespace std;

#define HALL_OF_FAME_FILENAME "HallOfFame.txt"

class Record{
public:
    string name;
    int points;

    Record(){
        name = "";
        points = 0;
    }
};

class HallOfFame{
    Record* records;
    int size;
    int capacity;

    void resize()
    {
        int i;
        Record* newRecords = new Record[capacity*2];
        for(i=0; i<capacity; i++)
        {
            newRecords[i].name = records[i].name;
            newRecords[i].points = newRecords[i].points;
        }

        delete[] records;
        records = newRecords;
        capacity = capacity*2;
    }
public:
    HallOfFame();
    void loadData();
    void addRecord(int points);
    void printHallOfFame();
    void sortHallOfFame();
    ~HallOfFame();
};

#endif //PROJECT_2048_GAME__HALLOFFAME_H
