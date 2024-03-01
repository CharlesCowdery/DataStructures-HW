#include "deck.h"
#include "deck_empty.h"

deck::deck() : front(nullptr), rear(nullptr), size(0) {}

deck::~deck() {
    while (!isEmpty()) {
        dequeue();
    }
}

void deck::enqueue(int value) {
    CardNode* newNode = new CardNode(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int deck::dequeue() {
    if (isEmpty()) {
        throw DeckEmpty();
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

int deck::getSize() const {
    return size;
}

bool deck::isEmpty() const {
    return size == 0;
}
