#ifndef BSTCustomer
#define BSTCustomer

#include <vector>
#include "Customer.cpp"

class CustomerSearchTree {
public:
    CustomerSearchTree() {
        for (int i = 0; i < 100; i++)
            tree_.push_back(nullptr);
    }

    // Insert a new element into the binary search tree
    void insert(Customer* c) {
        if (tree_.empty()) {
            tree_.push_back(nullptr);  // Index 0 is unused
            tree_.push_back(c);
        }
        else {
            insertHelper(1, c);
        }
    }

    // Traverse the binary search tree in-order and print each element
    void display() const {
        traverseHelper(1);
    }

private:
    std::vector<Customer*> tree_;

    // Recursive helper function to insert a new element into the binary search tree
    void insertHelper(int index, Customer* c) {
        if (tree_[index] == nullptr) {
            tree_[index] = c;
            tree_.push_back(nullptr);
        }
        else if (c->getName() < tree_[index]->getName()) {
            insertHelper(index * 2, c);
        }
        else {
            insertHelper(index * 2 + 1, c);
        }
    }

    // Recursive helper function to traverse the binary search tree in-order and print each element
    void traverseHelper(int index) const {
        if (tree_[index] == nullptr) {
            return;
        }
        traverseHelper(index * 2);
        tree_[index]->print_transactions();
        traverseHelper(index * 2 + 1);
    }
};

#endif