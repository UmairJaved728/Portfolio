#ifndef ROOM
#define ROOM

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

class Room{
	int roomNumber;		// Room number
	int numberOfSeats;	// Number of seats in the room
public:
	Room(int numSeats, int roomNum)
	{
		this->numberOfSeats = numSeats;
		this->roomNumber = roomNum;
	}

	int getNumberOfSeats() const{
		return numberOfSeats;
	}

	int getRoomNumber() const{
		return roomNumber;
	}

	void displayRoom()
    {
		// Shows the seating arrangement of the room
        cout << "\nROOM "<< roomNumber << "\n\n";
        cout << "------------------------- Seating -------------------------\n";
        for (int i = 1; i <= numberOfSeats; i++)
        {
            cout << i << '\t';
            if (i % 8 == 0)
                cout << '\n';
        }
        cout << "------------------------- END ---------------------------\n";
    }
};

#endif