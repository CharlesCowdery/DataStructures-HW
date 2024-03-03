#pragma once
#include <iostream>

class CardNode {
public:
    int value;
    CardNode* next;

    CardNode(int val) : value(val), next(nullptr) {}
};

class deck {
private:
    CardNode* front;
    CardNode* rear;
    int size;

public:
    deck();
    ~deck();
    void enqueue(int value);
    int dequeue();
    int getSize() const;
    bool isEmpty() const;
};