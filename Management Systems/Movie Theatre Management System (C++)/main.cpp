#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "./Cinema.cpp"
#include "./Cashier.cpp"
#include "./Manager.cpp"
#include "./Customer.cpp"

using namespace std;

//-----------Helper Functions
void Header();
void createCinema();
void createManager(bool isShow);
void ManagerPart();
void CustomerPart();
void customerRegister();
void existingCustomer();
void customersMenu(int index);
void ticketReservation();

//---------Global Objects
Cinema *cinema;
Manager *manager;
Room r1(30, 1), r2(40, 2), r3(45, 3);
Customer* customer[10];
int numberOfCustomers = 0;
CashDesk *cashDesk;
Cashier* cashier = NULL;

int main()
{
	int option;

	do{
		Header(); //prints Header
		createCinema(); // Creates a dummy cinema
		createManager(false);  //Creates manager
		cout << "  [1] Manager Part\n";
		cout << "  [2] Customer Part\n";
		cout << "  [3] Exit Application \n\n ";
		cout << "Select your option: ";
		cin >> option;
		switch (option)
		{
			case 1:
				ManagerPart();
				break;
			case 2:
				CustomerPart();
				break;
		}
	}while(option != 3);

	return 0;
}

void Header()
{
    system("cls");
    cout << "\n";

    //  ------ Upper Border -----
    cout << " \xC9";
    for (int i = 0; i < 76; i++)
        cout << "\xCD";
    cout << "\xBB";
    cout << "\n";
    // ----------------------------

    //  ------  Middle Border -----
    cout << " \xBA";
    //      [FROM_HERE                                                            TO_HERE]
    cout << "                          Cinema Business System                            ";
    cout << "\xBA";
    cout << "\n";
    // ----------------------------

    //  ------ Lower Border -----
    cout << " \xC8";
    for (int i = 0; i < 76; i++)
        cout << "\xCD";
    cout << "\xBC";
    cout << "\n\n";
    // ----------------------------
}

void createCinema()
{
	//-------------Cinema Address
	cinema = new Cinema("Didaskalou Avenue, 003-204, 34074, Tinos");
	//Creating 3 rooms
	cinema->addRoom(r1);
	cinema->addRoom(r2);
	cinema->addRoom(r3);
}

void createManager(bool isShow)
{
	// Creates manager with name and salary
	manager = new Manager(cinema, "Petroula Petrroulidou", 200000);
	
	// Creating movies objects
	Movie m1(11015, "The Nutcracker and the Four Realms", "English", "Drama, Fantasy U/A");
    Movie m2(11018, "The Travelling Players", "Greek", "Drama,Comedy,Family U");
    Movie m3(11025, "Smyrni mou Agaphmenh","Greek", "Drama, Family, Music, Romance U");
    Movie m4(11027, "A Star Is Born", "English", "Drama,Musical,Romance A");
    Movie m5(11009, "Hunter Killer", "English", "Action,Thriller U/A");

	// Adding movies by manager to bought
	manager->addMovieBought(m1);
	manager->addMovieBought(m2);
	manager->addMovieBought(m3);
	manager->addMovieBought(m4);
	manager->addMovieBought(m5);

	// Schduling movies with time and venue
	manager->addMoviesSchedule(m1, r1, "3/19/2022  10 AM" );
	manager->addMoviesSchedule(m2, r1, "3/19/2022  03 PM" );
	manager->addMoviesSchedule(m3, r2, "3/19/2022  08 PM" );
	manager->addMoviesSchedule(m4, r3, "3/22/2022  01 AM" );
	manager->addMoviesSchedule(m5, r3, "3/19/2022  11 PM" );
	
	// Showing movies details
	if(isShow)
		manager->showMovies();
}

void ManagerPart()
{
	Header();
	int option, isPay;
	do{
		cout << "  [1] Show Scheduled Movies\n";
		cout << "  [2] Report Total Earnings\n";
		cout << "  [3] Check Cashiers Bonus\n";
		cout << "  [4] Back \n\n";
		cout << "Select your option: ";
		cin >> option;
		switch(option)
		{
			case 1:
				createManager(true); // shows the movies list with time and venue
				break;
			case 2:
				cout << "Movies Bought and Scheduled is: " << '5' << "\n";
				cout << "Total Earnings are (Salary+Bonus): " << manager->getTotalEarning() << "\n\n"; 
				break;
			case 3:
				// If NULL, no ticket is purchased till now
				if(cashier==NULL)
					cout << "No ticket is purchased till now\n\n";
				else
				{
					cout << "Bonus of Cashier on the Cash Desk is " << cashier->getBonus() << '\n';
					cout << "Enter 1 to pay now or enter  anything to cancel: ";
					cin >> isPay;
					if(isPay==1)
					{
						cout << "\nBonus is Payed to Cashier\n\n";
						cashier->setBonus(0); 	//set bonus to 0 
					}
				}
				break;
		}
	}while(option != 4);
}

void CustomerPart()
{
	int option;
	cashDesk = new CashDesk(); 	//creates Cash Desk
	for( int i =0; i < 10; i++ )
		customer[i] = NULL;		//NULL shows customers which are not registered
	do{
		cout << "  [1] New Customer\n";
		cout << "  [2] Existing Customer\n";
		cout << "  [3] back \n\n";
		cout << "Select your option: ";
		cin >> option;
		switch (option)
		{
			case 1:
				customerRegister();	//Register the new customer
				break;
			case 2:
				existingCustomer();	// This function will call the existing customers
				break;
		}
	}while(option != 3);
}

void customerRegister()
{
	string name, password;
        while (true)
        {
            cout << "\n  Enter your name: ";
            cin >> name;
            cout << "  Enter your password: ";
            cin >> password;
            cout << "  Confirm your password: ";
            string confirm;
            cin >> confirm;
            if (password == confirm)
                break;
            else
                cout << "\nPasswords do not match. Try Again!\n";
        }

		// Assigns the new customer in to array
		customer[numberOfCustomers++] = new Customer(name, name, password);
        cout << "\nCongratulations, you are registered to our System\n\n";
		Header();
}

void existingCustomer()
{
	if(customer[0] == NULL)	// No Customers is registered till now
	{
		cout << "--------Please Register Yourself First!!----------\n\n";
		return;
	}

	string name, password;
	cout << "\n  Name: ";
	cin >> name;
	cout << "  Password: ";
	cin >> password;
	bool found = false;
	int index;
	// Authenticate Users
	for (int i = 0; i < numberOfCustomers; i++)
	{
		if (customer[i]->getUserName() == name && customer[i]->getPassword() == password)
		{
			index = i;
			found = true;
			break;
		}
	}
	cout << '\n';
	// User found
	if (found)
		customersMenu(index);
	else // Invalid user name or password
		cout << "--------------Invalid User--------------\n\n";
}

void customersMenu(int index)
{
	int option;
	Header();
	// Prints customer's name
	cout << "Welcome " << customer[index]->getUserName() << "!!\n\n";
	do{
        cout << "  [1] Ticket Reservation\n";
        cout << "  [2] Movies Timing\n";
        cout << "  [3] Show cinemaMap\n";
        cout << "  [4] Display Tickets\n";
        cout << "  [5] back \n\n";
        cout << "Select your option: ";
        cin >> option;
		Header();
        switch (option)
        {
			case 1:
				ticketReservation();
				break;
			case 2:
				createManager(true);
				break;
			case 3:
				cout << "Cinema has 3 Rooms with this Seating Arrangements...\n\n";
				r1.displayRoom();
				r2.displayRoom();
				r3.displayRoom();
				break;
			case 4:
				cashDesk->showTickets();
				break;
        }
	}while(option != 5 );
}

void ticketReservation()
{
	int movieOption, roomOption, seatNo, price;
	double bonus = 0, tip = 0;
	Ticket *t;
	Header();
	cashier = new Cashier(cashDesk, "Giorgos Giorgou", 70000); 	//creates a new cashier
	cout << "-----------------Welcome to Ticket Counter Number " << cashDesk->getDeskNumber() << "------------------\n\n";
	createManager(true);
	cout << "\n\n--------------- Available Movies -------------\n\n";
	cout << "Enter the Movie number: ";
	cin >> movieOption;

	cout << "Price of Room no 1 is $8\n";
	cout << "Price of Room no 2 is $6\n";
	cout << "Price of Room no 3 is $9\n\n";
	cout << "Enter the Room Number: ";
	cin >> roomOption;
	Room *r; // Selected room is pointed by this pointer
	if(roomOption == 1){
		r = &r1;
		price = 8;
	}
	else if(roomOption == 2){
		r = &r2;
		price = 6;
	}
	else {
		r = &r3;
		price = 9;
	}
	bonus += 50; // 50 bonus per ticket sale
	cout << "\n\n-------- Seating Arrangements ----------------\n\n";
	r->displayRoom();
	cout << "\n\nPlease Select a Seat: ";
	cin >> seatNo;
	switch(movieOption)
	{	// Selected movie will be added to sold Tickets vector.
		case 1: 
			t = new Ticket("The Nutcracker and the Four Realms", r->getRoomNumber(), seatNo, "3/19/2022  10 AM", price);
			cashDesk->saleTicket(*t);
			break;
		case 2: 
			t = new Ticket("Helicopter Eela", r->getRoomNumber(), seatNo, "3/19/2022  03 PM" , price);
			cashDesk->saleTicket(*t);
			break;
		case 3: 
			t = new Ticket("Smyrni mou Agaphmenh", r->getRoomNumber(), seatNo, "3/19/2022  08 PM", price);
			cashDesk->saleTicket(*t);
			break;
		case 4: 
			t = new Ticket("A Star Is Born", r->getRoomNumber(), seatNo, "3/22/2022  01 AM", price);
			cashDesk->saleTicket(*t);
			break;
		case 5: 
			t = new Ticket("Hunter Killer", r->getRoomNumber(), seatNo, "3/19/2022  11 PM", price);
			cashDesk->saleTicket(*t);
			break;
		default:
			cout << "\n\n--------------------Invalid Movie----------------\n\n";
			break;
	}
	cout << "All Done!! Enter any tip for the cashier(0 for no tip): ";
	cin >> tip;
	// Tip will added to the bonus
	bonus += tip;
	cashier->addBonus(bonus);
	cout << "\n\nSeat Number " << seatNo << " is reseved for you in room " << roomOption << "\n\n";
}