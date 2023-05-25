#ifndef BSTInventory
#define BSTInventory

#include <vector>
#include "Stocks.cpp"

class SearchTree{
public:
    SearchTree(){
        for(int i=0; i<100; i++)
            tree_.push_back(NULL);
    }

    // Insert a new element into the binary search tree
    void insert(Stocks* s) {
        if (tree_.empty()) {
            tree_.push_back(nullptr);  // Index 0 is unused
            tree_.push_back(s);
        } else {
            insertHelper(1, s);
        }
    }

    // Traverse the binary search tree in-order and print each element
    void traverse() const {
        traverseHelper(1);
    }

    // Remove an element with the given ID from the binary search tree
    void remove(Stocks* s) {
        removeHelper(1, s);
    }

    int count(char type){
        return countHelper(1, type);
    }

private:
    std::vector<Stocks*> tree_;

    // Recursive helper function to insert a new element into the binary search tree
    void insertHelper(int index, Stocks* s) {
        if (tree_[index] == nullptr) {
            tree_[index] = s;
            tree_.push_back(nullptr);
        } else if (s->compare( tree_[index]) < 0) {
            insertHelper(index * 2, s);
        } else {
            insertHelper(index * 2 + 1, s);
        }
    }

    // Recursive helper function to traverse the binary search tree in-order and print each element
    void traverseHelper(int index) const {
        if (tree_[index] == nullptr) {
            return;
        }
        traverseHelper(index * 2);
        tree_[index]->display();
        traverseHelper(index * 2 + 1);
    }

// Recursive helper function to remove an element with the given ID from the binary search tree
    void removeHelper(int index, Stocks* s) {
        if (tree_[index] == nullptr) {
            return;
        } else if (tree_[index]->compare(s) < 0) {
            removeHelper(index * 2, s);
        } else if (tree_[index]->compare(s) > 0) {
            removeHelper(index * 2 + 1, s);
        } else { // found node to remove
            if (tree_[index * 2] == nullptr && tree_[index * 2 + 1] == nullptr) { // Case 1: node has no children
                tree_[index] = nullptr;
            } else if (tree_[index * 2] == nullptr) { // Case 2: node has one child
                Stocks* temp = tree_[index];
                tree_[index] = tree_[index * 2 + 1];
                tree_[index * 2 + 1] = temp;
                removeHelper(index * 2 + 1, s);
            } else if (tree_[index * 2 + 1] == nullptr) { // Case 2: node has one child
                Stocks* temp = tree_[index];
                tree_[index] = tree_[index * 2];
                tree_[index * 2] = temp;
                removeHelper(index * 2, s);
            } else { // Case 3: node has two children
                Stocks* minNode = findMinNode(index * 2 + 1);
                Stocks* temp = tree_[index];
                tree_[index] = minNode;
                minNode = temp;
                removeHelper(index * 2 + 1, minNode);
            }
        }
    }

// Helper function to find the minimum node in the right subtree
    Stocks* findMinNode(int index) {
        while (tree_[index * 2] != nullptr) {
            index = index * 2;
        }
        Stocks* minNode = tree_[index];
        tree_[index] = nullptr;
        return minNode;
    }

    int countHelper(int index, char type){
        if (tree_[index] == nullptr) {
            return 0;
        }
        int count = 0;
        count += countHelper(index * 2, type);
        if(tree_[index]->getType() == type)
            count++;
        count += countHelper(index * 2 + 1, type);
        return count;
    }
};

#endif