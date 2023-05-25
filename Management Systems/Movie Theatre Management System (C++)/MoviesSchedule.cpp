#ifndef MOVIESSCHEDULE
#define MOVIESSCHEDULE

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Movie.cpp"
#include "./Room.cpp"

using namespace std;

class MoviesSchedule{
	Movie *movie;		// Movie object which is to be schduled
	string dateTime;	// date and time of the movie	
	Room *room;			// room in which which is played
  public:
    
	MoviesSchedule(Movie* movie, string dateTime, Room *room)
	{
		this->movie = movie;
		this->dateTime = dateTime;
		this->room = room;
	}

	Movie getMovie() const{
		return *movie;
	}
	string getMovieName() const{
		return movie->getName();
	}

	string getDateTime() const{
		return dateTime;
	}

	Room getRoom() const{
		return *room;
	}

	void display()
	{
		// Shows the details of only 1 movie which is scheduled.
		cout << "Movie Name: " << movie->getName() << '\n';
		cout << "Date and Time: " << dateTime << '\n';
		cout << "Room Number is " << 2 << '\n';
		cout << "..............................\n\n"; 
	}
};

#endif