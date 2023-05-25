#ifndef CUSTOMER
#define CUSTOMER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./User.cpp"
#include "./Ticket.cpp"

using namespace std;

class Customer : public User{
	string userName;		//Name of customer
	string password;		//password for customer
	vector<Ticket> ticketsBought;	//Tickets bought by the customer

  public:
    Customer(string name, string userName, string password) : User(name)
    {
		this->userName = userName;
		this->password = password;
    }

	void addTicketBought(Ticket &ticket){
		ticketsBought.push_back(ticket);
	}

	string getUserName() const{
		return userName;
	}
	string getPassword() const{
		return password;
	}
	
};

#endif