#ifndef BRANCH
#define  BRANCH

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Owner.cpp"
#include "./Client.cpp"
#include "./Agent.cpp"
#include "./Property.cpp"

using namespace std;

class Branch{
public:
	string address;
	float commission;
	float profitRate;
    vector<Owner> owners;
    vector<Client> clients;
    vector<Agent> agents;
    vector<Property> avaiableProperties;

    Branch(string address)
    {
        this->address = address;
		profitRate = 0.05;
    }

	int getNumberOfPropertiesSold()
	{
		int size = agents.size(), number = 0;
		for( int i = 0; i < size; i++ )
			number += agents[i].soldProperties.size();

		return number;
	}
};

#endif