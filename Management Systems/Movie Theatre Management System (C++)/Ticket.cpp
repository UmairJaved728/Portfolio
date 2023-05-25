#ifndef TICKET
#define TICKET

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Movie.cpp"

using namespace std;

class Ticket{
	// Ticket details
	string movieName; 	// name of movie of ticket
	int roomNumber;		
	int seatNumber;
	string date;
	double price;

  public:
    Ticket(string movieName, int roomNo, int seatNo, string date, double price)
    {
        this->movieName = movieName;
        this->roomNumber = roomNo;
        this->seatNumber = seatNo;
        this->price = price;
		this->date = date;
    }

	int getRoomNumber() const{
		return roomNumber;
	}

	int getSeatNumber() const{
		return seatNumber;
	}

	double getPrice() const{
		return price;
	}

	void display()
		{
			// Shows the details of the ticket
			cout << "Movie Name " << movieName << '\n';
			cout << "Room Number " << roomNumber << '\n';
			cout << "Seat Number " << seatNumber << '\n';
			cout << "Date " << date << '\n';
			cout << "..........................\n\n";
		}
};

#endif