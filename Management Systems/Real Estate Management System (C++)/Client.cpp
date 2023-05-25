#ifndef CLIENT
#define  CLIENT

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./User.cpp"
#include "./Owner.cpp"
#include "./Agent.cpp"
#include "./Property.cpp"

using namespace std;

class Client : public User{
public:
	vector<Owner> associatedOwners;
	vector<Agent> associatedAgents;
    vector<Property> propertiesPurchased;
    vector<Property> propertiesRented;

    Client(string name, string phone) : User(name, phone)
    {}

    void showPurchasedProperties()
    {
        cout << "\nThese Propertes are Puchased:\n\n";
        int size =  propertiesPurchased.size();
        if(size==0)
            cout << "\n--------------No Bought Properties Found-----------------\n\n";
        else 
        {
            for(int i=0; i < size; i++ )
            {
				cout << "Previous Owner of the Property: " << associatedOwners[i].getName() << '\n';
				cout << "Associated Agent of the Property: " << associatedAgents[i].getName() << '\n';
                propertiesPurchased[i].show();
                cout << "###############################\n\n";
            }
        }
    }

    void showRentedProperties()
    {
        cout << "\nThese Propertes are Rented:\n\n";
        int size = propertiesRented.size();
        if(size==0)
            cout << "\n--------------No Rented Properties Found-----------------\n\n";
        else 
        {
            for(int i=0; i < size; i++ )
            {
				cout << "Owner of the Property: " << associatedOwners[i].getName() << '\n';
				cout << "Associated Agent of the Property: " << associatedAgents[i].getName() << '\n';
                propertiesRented[i].show();
                cout << "###############################\n\n";
            }
        }
    }
};

#endif