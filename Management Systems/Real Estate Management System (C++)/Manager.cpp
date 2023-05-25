#ifndef MANAGER
#define  MANAGER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Branch.cpp"
#include "./Property.cpp"
#include "./Agent.cpp"
#include "./Owner.cpp"

using namespace std;

class Manager : public User{
public:
    vector<Branch> branches;
	vector<Agent> agents;
	vector<Owner> owners;
	vector<Property> properties;

    Manager(string name, string phone) : User(name, phone)
    {}

	void showAllAgentsProfits()
	{
		int i, j, size = branches.size();
		agents.clear();
		for( i=0; i<size;i++)
		{
			int size2 = branches[i].agents.size();
			for(j=0; j<size2; j++)
				agents.push_back(branches[i].agents[j]);
		}
		size = agents.size();
		for( i = 0; i < size; i++ )
		{
			cout << "Agent " << i + 1 << " : " << agents[i].name << '\n';
			agents[i].showProfitDetails();
		}
	}
    
    void showBranchesProfit()
    {
        int i, numberOfBranches = branches.size();
        cout << "\n\nTotal Number of Branches Exists: " << numberOfBranches << "\n\n";
        for( i = 0; i < numberOfBranches; i++ )
        {
			cout << "--------------------------------------\n";
			cout << "Branch " << i + 1 << '\n';
			cout << "Properties Sold: " << branches[i].getNumberOfPropertiesSold() << '\n';
			cout << "Commission Rate: " << branches[i].commission << '\n';
			cout << "Total Profit: " << branches[i].getNumberOfPropertiesSold() * branches[i].commission << '\n';
			cout << "---------------------------------------\n\n";
		}
    }

	void setCommissionOfAgency(float c)
	{
		int i, size = branches.size();
		for(i=0; i<size; i++)
			branches[i].commission = c;
	}

	void setProfitRateOfAgent(float p)
	{
		int i, size = branches.size();
		for(i=0; i<size; i++)
			branches[i].profitRate = p;
	}
};

#endif