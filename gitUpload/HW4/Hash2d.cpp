#include "Hash2D.h"
#include <iostream>
#include "Hash2DOverflow.h"
using namespace std;

Hash2d::Hash2d() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 5; j++) {
            nums[i][j] = -1;  // Indicates empty slot
        }
    }
}

Hash2d::~Hash2d() {}

int Hash2d::insert(int value) {
    int index = hash(value);
    int spotsChecked = 1;

    for (int i = 0; i < 5; i++) {
        if (nums[index][i] == -1) {
            nums[index][i] = value;
            return spotsChecked;
        }
        spotsChecked++;
    }
    throw HashOverflow();
}

int Hash2d::find(int value) {
    int index = hash(value);
    int spotsChecked = 1;

    for (int i = 0; i < 5; i++) {
        if (nums[index][i] == value) {
            return spotsChecked;
        }
        spotsChecked++;
    }
    return spotsChecked;
}

int Hash2d::remove(int value) {
    int index = hash(value);
    int spotsChecked = 0;

    for (int i = 0; i < 5; i++) {
        spotsChecked++;
        if (nums[index][i] == value) {
            nums[index][i] = -1;
            return spotsChecked;
        }
    }
    return spotsChecked;
}

void Hash2d::print() {
    for (int i = 0; i < 100; i++) {
        cout << "Slot " << i << ": ";
        for (int j = 0; j < 5; j++) {
            if (nums[i][j] == -1) {
                cout << "- ";
            }
            else {
                cout << nums[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int Hash2d::hash(int value) {
    return value % 100;
}