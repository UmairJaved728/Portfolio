#ifndef CASHDESK
#define CASHDESK

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Ticket.cpp"

using namespace std;

class CashDesk{
	int deskNumber;		//Desk number
	double totalEarning;	//Total earning per desk
	vector<Ticket> ticketsSold;	//Data of the tickets sold
	static int deskCount;	//Static variable to count for desk number
  public:
    
	CashDesk()
	{
		this->deskNumber = deskCount++;
		totalEarning = 0;
	}

	bool saleTicket(Ticket &ticket)
	{
		totalEarning += ticket.getPrice();
		ticketsSold.push_back(ticket);
		return true;
	}

	double getTotalEarning() const{
		return totalEarning;
	}

	int getDeskNumber() const{
		return deskNumber;
	}

	void showTickets()
	{
		int s = (int)ticketsSold.size();
		if(s==0)	//if no ticket is purchased
			cout << "\n------------- Purchase a Ticket First -----------------\n\n";
		for(int i =0; i<s; i++)
			ticketsSold[i].display();
	}
};
int CashDesk::deskCount = 1;

#endif