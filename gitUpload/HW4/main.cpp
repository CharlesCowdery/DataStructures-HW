#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "BinaryTree.h"
#include "Hash1d.h"
#include "Hash2d.h"


using namespace std;

int main() {
	int nums[100];
	int spots1d=0;
	int spots2d=0;
	int spotsBT=0;
	Hash1d h1;
	Hash2d h2;
	BinaryTree BT;
	for (int i = 0; i < 100; i++) {// getting the list of numbers
		nums[i] = rand() % 10000 + 1;
	}
	cout<<"inserting first 50 numbers" << endl;
	for (int i = 0; i < 50; i++) { //insert first 50 numbers
		spots1d += h1.insert(nums[i]);
		spots2d += h2.insert(nums[i]);
		spotsBT += BT.insert(nums[i]);
	}
	cout << "the spots checked for Binary tree: " << spotsBT << endl;
	cout << "the spots checked for 1d hash: " << spots1d << endl;
	cout << "the spots checked for 2d hash: " << spots2d << endl;
	spots1d = 0;
	spots2d = 0;
	spotsBT = 0;
	cout << "removing values round 1" << endl;
	for (int i = 0; i < 50; i++) {//removing every value from the array which index in nums %7 = 0 for the first 50 numbers
		if (i % 7 == 0) {
			spots1d += h1.remove(nums[i]);
			spots2d += h2.remove(nums[i]);
			spotsBT += BT.remove(nums[i]);
		}
	}
	cout << "the spots checked for Binary tree: " << spotsBT << endl;
	cout << "the spots checked for 1d hash: " << spots1d << endl;
	cout << "the spots checked for 2d hash: " << spots2d << endl;
	spots1d = 0;
	spots2d = 0;
	spotsBT = 0;
	cout << "inserting next 50"<<endl;
	for (int i = 50; i < 100; i++) { // inserting last 50 numbers
		spots1d += h1.insert(nums[i]);
		spots2d += h2.insert(nums[i]);
		spotsBT += BT.insert(nums[i]);
	}
	cout << "the spots checked for Binary tree: " << spotsBT << endl;
	cout << "the spots checked for 1d hash: " << spots1d << endl;
	cout << "the spots checked for 2d hash: " << spots2d << endl;
	spots1d = 0;
	spots2d = 0;
	spotsBT = 0;
	cout << "removing round 2" << endl;
	for (int i = 0; i < 100; i++) {// finding all of the numbers that the index in the main %9=0 not removing just finding
		if (i % 9 == 0) {
			spots1d += h1.find(nums[i]);
			spots2d += h2.find(nums[i]);
			spotsBT += BT.find(nums[i]);
		}
	
	}
	cout << "the spots checked for Binary tree: " << spotsBT << endl;
	cout << "the spots checked for 1d hash: " << spots1d << endl;
	cout << "the spots checked for 2d hash: " << spots2d << endl;
	spots1d = 0;
	spots2d = 0;
	spotsBT = 0;
	cout << "printing of the three structures:" << endl;
	cout << "1D hash:" << endl;
	h1.print();
	// cout << "2D hash:" << endl;
	// h2.print();
	// cout << "Binary Tree" << endl;
	// BT.print();

	return 1;
}
