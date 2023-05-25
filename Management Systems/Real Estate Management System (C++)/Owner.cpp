#ifndef OWNER
#define  OWNER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./User.cpp"
#include "./Property.cpp"

using namespace std;

class Owner : public User{
public:
	int profit;
    vector<Property> ownedProperties;
    vector<Property> soldProperties;
    vector<Property> rentedProperties;

    Owner(string name, string phone) : User(name, phone)
    {
        profit = 0;
    }

    void setPrices(int i, int s, int r)
    {
        ownedProperties[i].setPrices(s, r);
    }

    void addProperty(Property p)
    {
        ownedProperties.push_back(p);
    }

    void showAvailableProperties()
    {
        cout << "\n-------------------Owned Properties are : \n\n";
        int size = ownedProperties.size();
        for ( int i = 0; i < size; i++ )
        {
            ownedProperties[i].show();
            cout << "\n#####################################\n\n";
        }
    }

	void showSoldAndRentedProperties()
    {
        cout << "These Propertes are Sold:\n\n";
        int size =  soldProperties.size();
        if(size == 0)
            cout << "--------------No Properties are sold-------------\n\n";
        else
        {
            for(int i=0; i < size; i++ )
            {
                soldProperties[i].show();
                cout << "###############################\n\n";
            }
        }

		cout << "These Propertes are Rented:\n\n";
        size =  rentedProperties.size();
        if(size == 0)
            cout << "--------------No Properties are Rented-------------\n\n";
        else
        {
            for(int i=0; i < size; i++ )
            {
                rentedProperties[i].show();
                cout << "###############################\n\n";
            }
        }
    }
	void showProfitDetails()
	{
		cout << "\n-----------Profit Details of " << name << "---------------\n";
		cout << "Total Properties Sold: " << soldProperties.size() << '\n';
		cout << "Total Properties Rented: " << rentedProperties.size() << '\n';
		cout << "Total Profit Earned: " << profit << '\n';
		cout << "-----------------------------------------------------------\n";
	}
};

#endif