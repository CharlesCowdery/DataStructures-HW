#pragma once
#include <iostream>

class cardNode {
public:
    int value;
    cardNode* next;

    cardNode(int val) : value(val), next(nullptr) {}
};

class deck {
private:
    cardNode* front;
    cardNode* rear;
    int size;

public:
    deck();
    void enqueue(int value);
    int dequeue();
    int const getSize();
    bool const isEmpty();
};