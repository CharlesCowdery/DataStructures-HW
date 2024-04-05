#include "Hash1d.h"
#include <iostream>
using namespace std;

Hash1d::Hash1d() {
    for (int i = 0; i < 500; i++) {
            nums[i] = -1;  // Indicates empty slot
            flag[i] = false;
    }
}
Hash1d::~Hash1d() {}
int Hash1d::hash(int val) {
	return val % 500;
}
int Hash1d::insert(int val) {
	int index = hash(val);
    int comps = 1;
    while (nums[index] != -1) {
        index++;
            index = index % 500;
            comps++;
    }
    nums[index] = val;
    return comps;
}
int Hash1d::remove(int val) {
    int index = hash(val);
    int comps = 1;
    while (nums[index] != val&&!flag[index]&&comps>500) {
        index++;
        index = index % 500;
        comps++;
    }
    if (nums[index] == val) {
        nums[index] = -1;
        flag[index] = true;
    }
    return comps;
}
int Hash1d::find(int val) {
    int index = hash(val);
    int comps = 1;
    while (nums[index] != val && flag[index] && comps > 500) {
        index++;
        index = index % 500;
        comps++;
    }
    return comps;
}
void Hash1d::print() {
    for (int j = 0; j < 500; j++) {
        if (nums[j] == -1) {
            cout << "- ";
        }
        else {
            cout << nums[j] << " ";
        }
    }

}