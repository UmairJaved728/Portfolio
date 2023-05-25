#ifndef MOVIE
#define MOVIE

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

class Movie{
	int id;	//Movie unique id
	string name;	//movie name
	string language;	//movie language
	string classifications;	//movie classsifiction

  public:
    Movie(int id, string name, string language, string classifications)
    {
        this->id = id;
        this->name = name;
        this->language = language;
        this->classifications = classifications;
    }

	int getID() const{
		return id;
	}

	string getName() const{
		return name;
	}

	string getLanguage() const{
		return language;
	}

	string getClassification() const{
		return classifications;
	}
};

#endif