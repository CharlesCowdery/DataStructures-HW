#pragma once
#include <iostream>

class CardNode { // Definition of CardNode class
public:
    int value;
    CardNode* next; // Pointer to the next node in the deck

    CardNode(int val) : value(val), next(nullptr) {} // Constructor, sets next to nullptr
};

class deck { // Definition of deck class
private:
    CardNode* front; // Pointer to the first node in the deck
    CardNode* rear; // Pointer to the last node in the deck
    int size;

public:
    deck(); // Constructor for deck
    ~deck(); // Destructor for deck
    void enqueue(int value);
    int dequeue();
    int getSize() const;
    bool isEmpty() const;
};
