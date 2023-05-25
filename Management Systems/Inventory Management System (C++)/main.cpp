#include "Coins.cpp"
#include "ComicBooks.cpp"
#include "SportsCards.cpp"
#include "Inventory.cpp"
#include "Customer.cpp"
#include "HashTable.cpp"
#include "Stocks.cpp"
#include "BSTCustomer.cpp"
#include <bits/stdc++.h>

int main() {
    Inventory inventory;
    CustomerSearchTree cusSTree;
    //i.print_Inventory();

    //Customer File reading
    fstream customer;
    customer.open("Customer.txt", ios::in);
    if(customer.fail()) { //if file does not open for certain reasons
        cout << "\nFile cannot be open. Terminating Program......" << endl;
        exit(1);
    }

    vector<Customer*> cus;

    string id;
    string name;
    char comma;
    while (!customer.eof()){
        getline(customer, id, ',');
        getline(customer, name, '\n');
        Customer *cu = new Customer(id, name);
        cus.push_back(cu);
    }

    hashtable h(cus.size());
    for(int i=0;i<cus.size();i++){
        h.insert_customer(cus[i]);
        cusSTree.insert(cus[i]);
    }

    customer.close();
    cout << "\n----------------------------------------------\n";
    system("pause");
    fstream commands;
    commands.open("commands.txt", ios::in);
    if(commands.fail()) { //if file does not open for certain reasons
        cout << "\n\t\t\t\t\t\tFile cannot be open. Terminating Program......" << endl;
        exit(1);
    }

    //Data Reading
    char command_type;

    while (!commands.eof()){
        commands >> command_type;
        if( !(command_type == 'D' || command_type == 'H') )
            commands >> comma;
        cout << "\t" << command_type << "\n\n";
        if(command_type == 'S' || command_type == 'B'){
            Stocks* s;
            string customer_id;
            char type;
            getline(commands, customer_id, ',');

            commands >> type;
            commands >> comma;

            if(type=='M'){

                int year;
                string grade;
                string title;

                commands >> year;
                commands >> comma;

                getline(commands, grade, ',');
                getline(commands, title, '\n');
                s = new Coin(1, type, year, grade, title);
                //cout << customer_id << ' ' << type << ' ' << year << ' ' << grade << ' ' << title << endl;
            }

            else if(type == 'C'){
                int year;
                string grade;
                string title;
                string publisher;

                commands >> year;
                commands >> comma;

                getline(commands, grade, ',');
                getline(commands, title, ',');
                getline(commands, publisher, '\n');
                s = new ComicBooks(1, type, year, grade, title, publisher);
                //cout << customer_id << ' ' << type << ' ' << year << ' ' << grade << ' ' << title << " " << publisher <<  endl;
            }

            else if(type == 'S'){
                int year;
                string grade;
                string player;
                string manufacturer;

                commands >> year;
                commands >> comma;

                getline(commands, grade, ',');
                getline(commands, player, ',');
                getline(commands, manufacturer, '\n');
                s = new SportsCards(1, type, year, grade, player, manufacturer);
                //cout << customer_id << ' ' << type << ' ' << year << ' ' << grade << ' ' << player << " " << manufacturer <<  endl;
            }
            else{
                string t;
                getline(commands, t, '\n');
            }

            if(command_type == 'S'){
                Customer* c = h.get_customer(customer_id);
                if( c == nullptr )
                    cout << "Customer does not exists.\n\n";
                else {
                    inventory.remove(s);
                    s->set_status('B');
                    c->add_inventory(s);
                }
            }
            else
            {
                inventory.insert(s);
                Customer* c = h.get_customer(customer_id);
                s->set_status('S');
                c->add_inventory(s);
            }
        }
        else if(command_type == 'C'){
            string customer_id;
            getline(commands, customer_id, '\n');
            Customer* c = h.get_customer(id);
            if( c == nullptr )
                cout << "Customer does not exists.\n\n";
            else
                c->print_transactions();
        }
        else if( command_type == 'D' )
        {
            inventory.display();
        }
        else if( command_type == 'H' )
        {
            cusSTree.display();
        }
        else{
            string t;
            getline(commands, t, '\n');
        }

        system("pause");
    }
    commands.close();
    system("pause");
    return 0;
}
