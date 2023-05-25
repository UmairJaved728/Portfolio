#ifndef REALESTATE
#define REALESTATE

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

class Property{
    string address;
    bool isAvailable;
    float size;
    int numberOfRooms;
    string description;
    int salePrice;
    int rentPrice;
	bool saleOrRent;
public:
    Property(string address, int size, int numOfRooms, string des, int sPrice, int rPrice, bool isSale)
    {
        this->address = address;
        this->size = size;
        isAvailable = 1;
        this->description = des;
        this->numberOfRooms = numOfRooms;
        this->rentPrice = rPrice;
        this->salePrice = sPrice;
		this->saleOrRent = isSale;
    }

    void setPrices(int s, int p)
    {
        this->salePrice = s;
        this->rentPrice = p;
    }

    void setIsavailable(bool flag)
    {
        isAvailable = flag;
    }

    bool getIsAvailable()
    {
        return isAvailable;
    }

    int getPrice(bool isSale = true)
    {
		if( isSale )
	        return salePrice;
		else 
			return rentPrice;
    }

    int getNumberOfRooms()
    {
        return numberOfRooms;
    }

    void show() const{
		if( isAvailable )
		{
			cout << "Address: " << address << '\n';
			cout << "Size: " << size << " sq ft" << '\n';
			cout << description << '\n';
			cout << "Number of Rooms are : " << numberOfRooms << '\n';
			cout << "Selling Price: " << salePrice << '\n';
			cout << "Rental Price: " << rentPrice << '\n';
		}
    }
};

#endif