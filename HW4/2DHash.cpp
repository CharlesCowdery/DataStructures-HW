#include "LinearProbingHashTable.h"
#include <iostream>
using namespace std;

LinearProbingHashTable::LinearProbingHashTable() { // Constructor
    table = new int[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = -1;  // Indicates empty slot
    }
}

LinearProbingHashTable::~LinearProbingHashTable() { // Destructor
    delete[] table;
}

int LinearProbingHashTable::Insert(int value) { // Insert value into hash table
    int index = Hash(value);
    int spotsChecked = 1;

    while (table[index] != -1) { // Linear probing, find next empty slot
        index = (index + 1) % tableSize;
        spotsChecked++;
    }

    table[index] = value;
    return spotsChecked;
}

int LinearProbingHashTable::Find(int value) { // Find value in hash table
    int index = Hash(value);
    int spotsChecked = 1;

    while (table[index] != -1) { // Linear probing, search for the value
        if (table[index] == value) {
            return spotsChecked;
        }
        index = (index + 1) % tableSize;
        spotsChecked++;
    }

    return spotsChecked;
}

int LinearProbingHashTable::Remove(int value) { // Remove value from hash table
    int index = Hash(value);
    int spotsChecked = 1;

    while (table[index] != -1) { // Linear probing, search for the value and remove it
        if (table[index] == value) {
            table[index] = -1;
            return spotsChecked;
        }
        index = (index + 1) % tableSize;
        spotsChecked++;
    }
    return spotsChecked;
}

void LinearProbingHashTable::Print() { // Print hash table
    for (int i = 0; i < tableSize; i++) {
        if (table[i] == -1) {
            cout << " - ";  // Empty slot
        } else {
            cout << " " << table[i] << " ";  // Occupied slot
        }
    }
    cout << endl;
}

int LinearProbingHashTable::Hash(int value) { // Calculate the index based on the value
    return value % tableSize;
}