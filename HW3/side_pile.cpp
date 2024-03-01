#include "side_pile.h"
int side_pile::play() {
	if (length == 0) {
		throw "stack underflow";
	}
	length--;
	return pile[length];
}
void side_pile::add(int card) {
	if (length == 5) {
		throw "stack overflow";
	}
	length++;
	pile[length] = card;
}
int side_pile::getlength() {
	return length;
}
