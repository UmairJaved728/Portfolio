#ifndef HASH
#define HASH
#include "Customer.cpp"

#include <bits/stdc++.h>

using namespace std;

class hashtable{
    vector<vector<Customer*>> customer_table;
    int size;
public:

    hashtable(int size){
        this->size=size;
        for(int i=0;i<size;i++){
            customer_table.push_back(vector<Customer*>());
        }
    }
    // Hash function for the Customer class
    int hash_customer(const Customer& c, int table_size) {
        return stoi(c.getId()) % table_size;
    }

    void insert_customer(Customer* c) {
        int index = hash_customer(*c, customer_table.size());
        customer_table[index].push_back(c);
    }

// Retrieve a customer from the hash table by ID
    Customer* get_customer(string id) {
        Customer* c = new Customer(id, "");
        int index = hash_customer(*c, customer_table.size());
        for (int i = 0; i < customer_table[index].size(); i++) {
            if (customer_table[index][i]->getId() == id) {
                return customer_table[index][i];
            }
        }
        return nullptr;
    }

};





#endif