#include "deck.h"
#include "deck_empty.h"

deck::deck() : front(nullptr), rear(nullptr), size(0) {} // Constructor

deck::~deck() { // Destructor
    while (!isEmpty()) {
        dequeue();
    }
}

void deck::enqueue(int value) { // Adds a new card with the specified value to the end of the deck
    CardNode* newNode = new CardNode(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int deck::dequeue() { // Removes a card from the front of the deck and returns its value
    if (isEmpty()) {
        throw DeckEmpty();
    }
    CardNode* temp = front; // Temporarily store the front node
    int value = temp->value; // Move the front pointer to the next node
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    size--;
    return value;
}

int deck::getSize() const { // Returns current size of deck
    return size;
}

bool deck::isEmpty() const { // Returns whether deck is empty
    return size == 0;
}
