#ifndef CINEMA
#define CINEMA

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./MoviesSchedule.cpp"
#include "./Room.cpp"
#include "./CashDesk.cpp"

using namespace std;

class Cinema{
	string address;	//address of cinema
	vector<Room> rooms;	//Rooms in the cinema
	vector<CashDesk> cashDesks;		//CashDesks in the cinema
	vector<MoviesSchedule> moviesPlaying;	//Movies that are currently playing
  public:

	Cinema(string address)
	{
		this->address =address;
	}

	void addRoom(Room room)
	{
		rooms.push_back(room);
	}

	void addMoviesSchedule(MoviesSchedule schedule)
	{
		moviesPlaying.push_back(schedule);
	}

	void addCashDesk(CashDesk cashDesk)
	{
		cashDesks.push_back(cashDesk);
	}
	
	vector<Room> getRoom() const{
		return rooms;
	}

	vector<MoviesSchedule> getMoviesSchedule() const{
		return moviesPlaying;
	}

	vector<CashDesk> getCashDesk() const{
		return cashDesks;
	}
};

#endif