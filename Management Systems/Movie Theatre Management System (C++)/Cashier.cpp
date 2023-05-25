#ifndef CASHIER
#define CASHIER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./User.cpp"
#include "./CashDesk.cpp"

using namespace std;

class Cashier : public User{
	CashDesk* cashDesk;		//Cash desk on which cahier is assigned
	double salary;			// Salary of cashier
	double bonus;			// Bonus per ticket sold

  public:
    Cashier(CashDesk* cashDesk, string name, double salary) : User(name)
    {
		this->cashDesk = cashDesk;
		this->salary = salary;
    }

	void setBonus(double bonus)
	{
		this->bonus = bonus;
	}

	void addBonus(double bonus)
	{
		this->bonus += bonus;
	}

	double getBonus() const{
		return bonus;
	}
};

#endif