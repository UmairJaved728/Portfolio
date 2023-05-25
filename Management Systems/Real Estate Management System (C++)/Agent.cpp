#ifndef AGENT
#define  AGENT

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./User.cpp"
#include "./Owner.cpp"
#include "./Property.cpp"

using namespace std;

class Agent : public User{
public:
    int profit;
    vector<Property> avaiableProperties;
    vector<Property> soldProperties;
    vector<Property> rentedProperties;
	vector<Owner> owners;

    Agent(string name, string phone) : User(name, phone)
    {
        profit = 0;
    }

    void showAvailableProperties(int min=0, int max=999999999, bool isFilterByRooms=true)
    {
        cout << "\nThese Propertes are Available by the agent " << name << ": \n\n";
        int size =  avaiableProperties.size();
        if(size == 0)
            cout << "--------------No Availavle Properties by " << User::getName() << "-------------\n\n";
        else
        {
            for(int i=0; i < size; i++ )
            {
                if( !isFilterByRooms && avaiableProperties[i].getPrice() >= min && avaiableProperties[i].getPrice() <= max )
				{
					cout << "Owner of Property is " << owners[i].name << '\n';
                    avaiableProperties[i].show();
				}
                else if( isFilterByRooms && avaiableProperties[i].getNumberOfRooms() >= min && avaiableProperties[i].getNumberOfRooms() <= max )
				{
					cout << "Owner of Property is " << owners[i].getName() << '\n';
                    avaiableProperties[i].show();
				}
                cout << "###############################\n\n";
            }
        }
    }

    void showReport()
    {
        cout << "These Propertes are Sold by " << name << ":\n\n";
        int size =  soldProperties.size();
        if(size == 0)
            cout << "--------------No Properties are sold by " << User::getName() << "-------------\n\n";
        else
        {
            for(int i=0; i < size; i++ )
            {
                soldProperties[i].show();
                cout << "###############################\n\n";
            }
        }

		cout << "These Propertes are Rented by " << name << ":\n\n";
        size =  rentedProperties.size();
        if(size == 0)
            cout << "--------------No Properties are Rented by " << User::getName() << "-------------\n\n";
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