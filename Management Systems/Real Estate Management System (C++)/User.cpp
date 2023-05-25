#ifndef USER
#define  USER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

class User{
public:
    string name;
	string phone;
    User(string name, string phone)
    {
        this->name = name;
		this->phone = phone;
    }

    string getName()
    {
        return name;
    }

    string getPhone()
    {
        return phone;
    }
};

#endif