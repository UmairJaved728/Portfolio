#ifndef USER
#define USER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

class User{
	string name;	//name of user

  public:
    User(string name)
    {
		this->name = name;
    }

	string getName() const{
		return name;
	}
};

#endif