#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Agent.cpp"
#include "./Branch.cpp"
#include "./Client.cpp"
#include "./Manager.cpp"
#include "./Owner.cpp"
#include "./Property.cpp"

using namespace std;

//Helper Functions
void printHeader();
void makeInitialData();
void selectBranch();
void ownerPart();
void agentPart();
void clientPart();
void managerPart();

//Global Objects
Manager *manager = new Manager("Stavros Stavrou", "6945454545");
int selectedBranch = 0;

int main()
{
	
	makeInitialData();

	int option; 

	do{
		printHeader();

		cout << "\tBranch " << selectedBranch + 1 << " is selected with Address: " << manager->branches[selectedBranch].address << "\n\n";

		cout << "  [1] Select Branch\n";
		cout << "  [2] Owner Part\n";
		cout << "  [3] Agent Part\n";
		cout << "  [4] Client Part\n";
		cout << "  [5] Manager Part\n";
		cout << "  [6] Exit Application \n\n ";
		cout << "Select your option: ";
		cin >> option;

		switch (option)
		{
			case 1:
				selectBranch();
				break;
			case 2:
				ownerPart();
				break;
			case 3:
				agentPart();
				break;
			case 4:
				clientPart();
				break;
			case 5: 
				managerPart();
				break;
		}
	}while(option != 6);

	return 0;
}

void printHeader()
{
//    system("clear");	// For Linux users uncooment this line
	system("cls");	// For Windows users uncooment this line
	cout << "\t ______                        ______   _____                                       \n";
	cout << "\t|      |     /\\      |\\     | |      | |     |    /\\      |\\    /|       /\\      \n";
	cout << "\t|      |    /  \\     | \\    | |      | |     |   /  \\     | \\  / |      /  \\     \n";
	cout << "\t|      |   /    \\    |  \\   | |      | |_____|  /    \\    |  \\/  |     /    \\    \n";
	cout << "\t|______|  /______\\   |   \\  | |      | |\\      /______\\   |      |    /______\\   \n";
	cout << "\t|        /        \\  |    \\ | |      | | \\    /        \\  |      |   /        \\  \n";
	cout << "\t|       /          \\ |     \\| |______| |  \\  /          \\ |      |  /          \\ \n";
    cout << "\n";

    //  ------ Upper Border -----
    cout << " \xC9";
    for (int i = 0; i < 90; i++)
        cout << "\xCD";
    cout << "\xBB";
    cout << "\n";
    // ----------------------------

    //  ------  Middle Border -----
    cout << " \xBA";
    //      [FROM_HERE                                                            TO_HERE]
    cout << "                                        Real Estate                                       ";
    cout << "\xBA";
    cout << "\n";
    // ----------------------------

    //  ------ Lower Border -----
    cout << " \xC8";
    for (int i = 0; i < 90; i++)
        cout << "\xCD";
    cout << "\xBC";
    cout << "\n\n";
    // ----------------------------
}

void makeInitialData()
{
	Branch *branch1 = new Branch("15 Merarchias Street, Kastoria, Greece");
	Branch *branch2 = new Branch("Agiou Dimitriou Street, Kastoria, Greece");

	manager->branches.push_back(*branch1);
	manager->branches.push_back(*branch2);

	int i, size = manager->branches.size();
	for(i=0; i<size; i++)
		manager->branches[i].commission = 9000;
	for(i=0; i<size; i++)
		manager->branches[i].profitRate = 0.05;

	Owner *owner1 = new Owner("Giorgos Giorgou", "6945454545");
	Owner *owner2 = new Owner("Petros Petrou", "6945454545");
	Owner *owner3 = new Owner("Maria Mariou", "6945454545");

	manager->owners.push_back(*owner1);
	manager->owners.push_back(*owner2);
	manager->owners.push_back(*owner3);

	manager->branches[0].owners.push_back(*owner1);
	manager->branches[0].owners.push_back(*owner2);
	manager->branches[1].owners.push_back(*owner3);

	Property *property1 = new Property("3/40 Syntagmatos Evzonon Street, Arta Greece", 225, 4, "White painted house at beautiful location.", 2750000, 30000, true);
    Property *property2 = new Property("7 Chroni Gianni Street, Corfu Greece", 190, 3, "Well Furnished and decorated.", 2350000, 23000, true);
    Property *property3 = new Property("16 Taxiarchias Street, Kavala Greece", 250, 6, "Large and Affordable in a best quality.", 3550000, 37000, false);	
	Property *property4 = new Property("Alvanou Anas. Street, Kastoria Greece", 150, 3, "Large and Affordable and White painted house", 3405000, 27000, false);	
	Property *property5 = new Property("Apolloniados Street, Kastoria Greece", 270, 5, "Large and Affordable in a best quality.", 4510000, 45000, true);	

	manager->properties.push_back(*property1);
	manager->properties.push_back(*property2);
	manager->properties.push_back(*property3);
	manager->properties.push_back(*property4);
	manager->properties.push_back(*property5);

	manager->branches[0].owners[0].ownedProperties.push_back(*property1);
	manager->branches[0].owners[0].soldProperties.push_back(*property2);
	manager->branches[0].owners[0].profit += manager->branches[0].profitRate * property2->getPrice();
	manager->branches[0].owners[1].ownedProperties.push_back(*property3);
	manager->branches[0].owners[1].ownedProperties.push_back(*property4);
	manager->branches[0].owners[1].rentedProperties.push_back(*property5);
	manager->branches[0].owners[1].profit += manager->branches[0].profitRate * property2->getPrice();
	manager->branches[1].owners[0].ownedProperties.push_back(*property3);
	manager->branches[1].owners[0].soldProperties.push_back(*property5);
	manager->branches[1].owners[0].profit += manager->branches[1].profitRate * property5->getPrice();
	manager->branches[1].owners[0].rentedProperties.push_back(*property1);

	manager->branches[0].avaiableProperties.push_back(*property1);
	manager->branches[0].avaiableProperties.push_back(*property4);
	manager->branches[0].avaiableProperties.push_back(*property3);
	manager->branches[1].avaiableProperties.push_back(*property3);

	Agent *agent1 = new Agent("Katerina Katerinou", "6945454545");
	Agent *agent2 = new Agent("Fwths Fwtiou", "6945454545");
	Agent *agent3 = new Agent("Achilleas", "6945454545");

	manager->branches[0].agents.push_back(*agent1);
	manager->branches[0].agents.push_back(*agent2);
	manager->branches[1].agents.push_back(*agent2);
	manager->branches[1].agents.push_back(*agent3);

	manager->branches[0].agents[0].avaiableProperties.push_back(*property1);
	manager->branches[0].agents[0].owners.push_back(*owner1);
	manager->branches[0].agents[0].soldProperties.push_back(*property2);
	manager->branches[0].agents[0].profit += manager->branches[0].profitRate * property2->getPrice();
	manager->branches[0].agents[1].avaiableProperties.push_back(*property3);
	manager->branches[0].agents[1].avaiableProperties.push_back(*property4);
	manager->branches[0].agents[1].profit += manager->branches[0].profitRate * property2->getPrice(false);
	manager->branches[0].agents[1].owners.push_back(*owner2);
	manager->branches[0].agents[1].owners.push_back(*owner2);
	manager->branches[0].agents[1].rentedProperties.push_back(*property5);
	manager->branches[1].agents[0].avaiableProperties.push_back(*property3);
	manager->branches[1].agents[0].soldProperties.push_back(*property5);
	manager->branches[1].agents[0].profit += manager->branches[1].profitRate * property5->getPrice();
	manager->branches[1].agents[0].rentedProperties.push_back(*property1);
	manager->branches[1].agents[0].owners.push_back(*owner3);

	Client *client1 = new Client("Agnieszka", "6945454545");
	Client *client2 = new Client("Damokles", "6945454545");
	Client *client3 = new Client("Eudokia", "6945454545");

	manager->branches[0].clients.push_back(*client1);
	manager->branches[0].clients.push_back(*client2);
	manager->branches[1].clients.push_back(*client3);

	manager->branches[0].clients[0].propertiesPurchased.push_back(*property2);
	manager->branches[0].clients[0].associatedOwners.push_back(*owner1);
	manager->branches[0].clients[0].associatedAgents.push_back(*agent1);


	manager->branches[0].clients[1].propertiesRented.push_back(*property5);
	manager->branches[0].clients[1].associatedOwners.push_back(*owner2);
	manager->branches[0].clients[1].associatedAgents.push_back(*agent2);

	manager->branches[1].clients[0].propertiesRented.push_back(*property1);
	manager->branches[1].clients[0].propertiesPurchased.push_back(*property5);
	manager->branches[1].clients[0].associatedOwners.push_back(*owner3);
	manager->branches[1].clients[0].associatedAgents.push_back(*agent3);	
}

void selectBranch()
{
	printHeader();
	cout << "  [1] Branch 1 : " << manager->branches[0].address << '\n';
	cout << "  [2] Branch 2 : " << manager->branches[1].address << '\n';

	cout << "\nEnter Your choice: ";
	cin >> selectedBranch;
	
	selectedBranch--;
}

void ownerPart()
{
	int option, size = manager->branches[selectedBranch].owners.size(), selectedPerson; 
	int numRooms, sPrice, rPrice, saleOrRent, selectedProperty, selectedAgent;
    string address, description;
	Property *property;
	printHeader();

	cout << "The list of all available Owners is as follows:\n\n";
	for(int i = 0; i < size; i++)
		cout << "  [ " << i+1 << " ]  " << manager->branches[selectedBranch].owners[i].name << '\n';

	cout << "\nSelect an Owner: ";
	cin >> selectedPerson;

	printHeader();
	selectedPerson--;

	do{
		cout << "\nWelcome " << manager->branches[selectedBranch].owners[selectedPerson].name << "\n\n";
		cout << "  [1] Add new Property\n";
		cout << "  [2] Change Prices of Property\n";
		cout << "  [3] Assign Property to Agent\n";
		cout << "  [4] View Avaiable Properties\n";
		cout << "  [5] View Sold/Rented Properties\n";
		cout << "  [6] View Profit\n";
		cout << "  [7] Go Back\n\n ";

		cout << "Select your option: ";
		cin >> option;

		switch (option)
		{
			case 1:
				cout << "Enter Address: ";
				cin >> address;
				cout << "Enter Size in square feet: ";
				cin >> size;
				cout << "Enter Number of Rooms: ";
				cin >> numRooms;
				cout << "Enter Description: ";
				cin >> description;
				cout << "Enter Sale Price: ";
				cin >> sPrice;
				cout << "Enter Rent Price: ";
				cin >> rPrice;
				cout << "Do you want to sale or rent this property(1 for sale and 0 for rent): ";
				cin >> saleOrRent;
				property = new Property(address, size, numRooms, description, sPrice, rPrice, saleOrRent);
				manager->branches[selectedBranch].owners[selectedPerson].addProperty(*property);
				manager->branches[selectedBranch].avaiableProperties.push_back(*property);
				cout << "\n\nProperty Successfuly Addedd!!!\n\n";
				break;
			case 2: 
				cout << "These are the available Properties:\n\n";
				manager->branches[selectedBranch].owners[selectedPerson].showAvailableProperties();
				cout << "\n\nEnter the Property Number: ";
				cin >> selectedProperty;
				selectedProperty--;
				cout << "\n\tEnter New Sale Price: ";
				cin >> sPrice;
				cout << "\n\tEnter New Rent Price: ";
				cin >> rPrice;
				manager->branches[selectedBranch].owners[selectedPerson].setPrices(selectedProperty, sPrice, rPrice);
				cout << "\nPrices Successfully Changed!!\n\n";
				break;

			case 3:
				size = manager->branches[selectedBranch].agents.size();
				cout << "These are the Agents in this branch:\n\n";
				for(int i = 0; i < size; i++)
					cout << "  [ " << i+1 << " ]   " << manager->branches[selectedBranch].agents[i].name << '\n';
				cout << "\nSelect an Agent: ";
				cin >> selectedAgent;
				selectedAgent--;
				cout << "Enter the Property Number You want to assign: ";
				cin >> selectedProperty;
				selectedProperty--;
				manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties.push_back(manager->branches[selectedBranch].owners[selectedPerson].ownedProperties[selectedProperty]);
				cout << "\nProperty is successfully Assigned!!\n\n";
				break;
			case 4:
				manager->branches[selectedBranch].owners[selectedPerson].showAvailableProperties();
				break;
			case 5:
				manager->branches[selectedBranch].owners[selectedPerson].showSoldAndRentedProperties();
				break;
			case 6:
				manager->branches[selectedBranch].owners[selectedPerson].showProfitDetails();
				break;
		}
	}while(option != 7);
}

void agentPart()
{
	int size, selectedAgent, option;
	size = manager->branches[selectedBranch].agents.size();
	printHeader();
	cout << "These are the Agents in this branch:\n\n";
	for(int i = 0; i < size; i++)
		cout << "  [ " << i+1 << " ]   " << manager->branches[selectedBranch].agents[i].name << '\n';
	cout << "\nSelect an Agent: ";
	cin >> selectedAgent;
	selectedAgent--;

	printHeader();
	
	do{
		cout << "\n  [1] Print Sales/Rental report of the Agent\n";
		cout << "  [2] Show Profit Report\n";
		cout << "  [3] Go Back\n\n";

		cout << "Select your option: ";
		cin >> option;

		switch (option)
		{
			case 1:
				manager->branches[selectedBranch].agents[selectedAgent].showReport();
				break;
			case 2:
				cout << "\n Profit Percentage for properties price is: " <<  manager->branches[selectedBranch].profitRate << '\n';
				manager->branches[selectedBranch].agents[selectedAgent].showProfitDetails();
				break;
		}
	}while(option != 3);
}

void clientPart()
{
	int size, selectedClient, option, min, max, i, selectedAgent, selectedProperty;
	size = manager->branches[selectedBranch].clients.size();
	printHeader();
	cout << "These are the Registered Clients in this branch:\n\n";
	for(int i = 0; i < size; i++)
		cout << "  [ " << i+1 << " ]   " << manager->branches[selectedBranch].clients[i].name << '\n';
	cout << "\nSelect a Client: ";
	cin >> selectedClient;
	selectedClient--;

	printHeader();
	
	do{
		cout << "\n  [1] Set Price Range\n";
		cout << "  [2] Set Rooms Range\n";
		cout << "  [3] Buy a property\n";
		cout << "  [4] Rent a property\n";
		cout << "  [5] View Bought Properties\n";
		cout << "  [6] View Rented Properties\n";
		cout << "  [7] Go Back\n\n";

		cout << "Select your option: ";
		cin >> option;

		switch (option)
		{
			case 1:
				cout << "Enter the Minimum Price: ";
				cin >> min;
				cout << "Enter the maximum Price: ";
				cin >> max;
				cout << "The Available properties in this price range is as follows,\n\n";
				size = manager->branches[selectedBranch].agents.size();
				for(i =0; i < size; i++ )
					manager->branches[selectedBranch].agents[i].showAvailableProperties(min, max, false);
				break;
			case 2:
				cout << "Enter the Minimum Number of rooms: ";
				cin >> min;
				cout << "Enter the maximum Number of rooms: ";
				cin >> max;
				cout << "The Available properties in this Rooms range is as follows,\n\n";
				size = manager->branches[selectedBranch].agents.size();
				for(i =0; i < size; i++ )
					manager->branches[selectedBranch].agents[i].showAvailableProperties(min, max);
				break;
			case 3: 
				size = manager->branches[selectedBranch].agents.size();
				cout << "These are the Agents in this branch:\n\n";
				for(int i = 0; i < size; i++)
					cout << "  [ " << i+1 << " ]   " << manager->branches[selectedBranch].agents[i].name << '\n';
				cout << "\nSelect an Agent: ";
				cin >> selectedAgent;
				selectedAgent--;
				cout << "Properties available for sale are as follows:\n\n";
				manager->branches[selectedBranch].agents[selectedAgent].showAvailableProperties();
				cout << "\n\nEnter the number of Property you want to buy: ";
				cin >> selectedProperty;
				selectedProperty--;
				manager->branches[selectedBranch].clients[selectedClient].propertiesPurchased.push_back(manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties[selectedProperty]);
				manager->branches[selectedBranch].clients[selectedClient].associatedAgents.push_back(manager->branches[selectedBranch].agents[selectedAgent]);
				manager->branches[selectedBranch].clients[selectedClient].associatedOwners.push_back(manager->branches[selectedBranch].agents[selectedAgent].owners[selectedProperty]);
				manager->branches[selectedBranch].agents[selectedAgent].soldProperties.push_back(manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties[selectedProperty]);
				manager->branches[selectedBranch].agents[selectedAgent].profit += manager->branches[selectedBranch].profitRate * manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties[selectedProperty].getPrice();
				cout << "\n\nProperty Successfully Bought!!\n\n";
				break;
			case 4: 
				size = manager->branches[selectedBranch].agents.size();
				cout << "These are the Agents in this branch:\n\n";
				for(int i = 0; i < size; i++)
					cout << "  [ " << i+1 << " ]   " << manager->branches[selectedBranch].agents[i].name << '\n';
				cout << "\nSelect an Agent: ";
				cin >> selectedAgent;
				selectedAgent--;
				cout << "Properties available for Rent are as follows:\n\n";
				manager->branches[selectedBranch].agents[selectedAgent].showAvailableProperties();
				cout << "\n\nEnter the number of Property you want to Rent: ";
				cin >> selectedProperty;
				selectedProperty--;
				manager->branches[selectedBranch].clients[selectedClient].propertiesRented.push_back(manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties[selectedProperty]);
				manager->branches[selectedBranch].clients[selectedClient].associatedAgents.push_back(manager->branches[selectedBranch].agents[selectedAgent]);
				manager->branches[selectedBranch].clients[selectedClient].associatedOwners.push_back(manager->branches[selectedBranch].agents[selectedAgent].owners[selectedProperty]);
				manager->branches[selectedBranch].agents[selectedAgent].rentedProperties.push_back(manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties[selectedProperty]);
				manager->branches[selectedBranch].agents[selectedAgent].profit += manager->branches[selectedBranch].profitRate * manager->branches[selectedBranch].agents[selectedAgent].avaiableProperties[selectedProperty].getPrice(false);
				cout << "\n\nProperty Successfully Rented!!\n\n";
				break;
			case 5:
				manager->branches[selectedBranch].clients[selectedClient].showPurchasedProperties();
				break;
			case 6:
				manager->branches[selectedBranch].clients[selectedClient].showRentedProperties();
				break;
		}
	}while(option != 7);
}

void managerPart()
{
	int option;
	float percent;

	printHeader();
	
	do{
		cout << "\n  [1] Show All Branches Profits\n";
		cout << "  [2] Show All Agents Profits\n";
		cout << "  [3] Set Commission Percentage of the agency\n";
		cout << "  [4] Set Profit Percentage of the Agents\n";
		cout << "  [5] Go Back\n\n";

		cout << "Select your option: ";
		cin >> option;

		switch (option)
		{
			case 1:
				manager->showBranchesProfit();
				break;
			case 2:
				manager->showAllAgentsProfits();
				break;
			case 3:
				cout << "Current Commission per property of Agency is : " << manager->branches[selectedBranch].commission;
				cout << "\nEnter the New Commission per property: ";
				cin >> percent;
				manager->setCommissionOfAgency(percent);
				cout << "\nCommission is successfully Changed to " << percent << "\n\n";
				break;
			case 4:
				cout << "Current Profit Percentage of agents is : " << manager->branches[selectedBranch].profitRate;
				cout << "\nEnter the New Profit Rate for agents: ";
				cin >> percent;
				manager->setProfitRateOfAgent(percent);
				cout << "\nProfit rate of agenrs is successfully Changed to " << percent << "\n\n";
				break;
		}
	}while(option != 5);
}
