#include "deck.h"

Deck::Deck() : front(nullptr), rear(nullptr), size(0) {}

Deck::~Deck() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Deck::enqueue(int value) {
    CardNode* newNode = new CardNode(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int Deck::dequeue() {
    if (isEmpty()) {
        throw "stack underflow"
    }
    CardNode* temp = front;
    int value = temp->value;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    size--;
    return value;
}

int Deck::getSize() const {
    return size;
}

bool Deck::isEmpty() const {
    return size == 0;
}