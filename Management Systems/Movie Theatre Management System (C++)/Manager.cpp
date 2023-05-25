#ifndef MANAGER
#define MANAGER

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./User.cpp"
#include "./Cinema.cpp"
#include "./MoviesSchedule.cpp"
#include "./Movie.cpp"
#include "./Room.cpp"

using namespace std;

// Inherits User
class Manager : public User {
	Cinema *cinema;			// Cinema details for manager
	vector<Movie> moviesBought;		//Movies bought by the manager
	double totalEarning;		//Total earnings per movie
	double salary;			//Salary of manager
	double bonus;			//Bonus of the manager
	vector<MoviesSchedule> moviesScheduled; //Movies scheduled
  public:
    Manager(Cinema* cinema, string name, double salary) : User(name)
    {
		this->bonus = 0;
		this->cinema = cinema;
		this->salary = salary;
		this->totalEarning = salary + bonus;
    }

	void addMovieBought(Movie &movie)
	{
		moviesBought.push_back(movie);
	}

	void addMoviesSchedule(Movie &movie, Room room, string dateTime)
	{
		//scheduled movies added by the manager
		MoviesSchedule schedule(&movie, dateTime, &room);
		moviesScheduled.push_back(schedule);
	}

	bool addMovieSchedule(Movie movie, Room room, string dateTime)
	{
		//scheduled Movies added to the cinema
		MoviesSchedule schedule(&movie, dateTime, &room);
		cinema->addMoviesSchedule(schedule);
		calculateBonus(2000);
		return true;
	}

	void calculateBonus(int bonus){
		this->bonus += bonus;
		totalEarning += bonus;
	}

	double getTotalEarning() const{
		return totalEarning;
	}

	void showMovies()
	{
		// Shows the details of all the scheduled movies with time and venue
		int size = (int)(moviesScheduled.size());
		for(int i=0; i < size; i++)
		{
			cout << "Movie No. " << i + 1 << '\n';
			moviesScheduled[i].display();
		}
	}

	Cinema* getCinema() const{
		return cinema;
	}

	string getName() const{
		return User::getName();
	}
};

#endif