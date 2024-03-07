#include "side_pile.h"
#include "side_pile_empty.h"
#include "side_pile_full.h"
//constructor and destructor for side pile
side_pile::side_pile() {}
side_pile::~side_pile() {};
//plays a card if its not empty
int side_pile::play() {
	if (length == 0) {
		throw StackEmpty();
	}
	length--;
	return pile[length];
}
//adds a card if it is not full
void side_pile::add(int card) {
	if (length == 5) {
		throw StackFull();
	}
	pile[length] = card;
	length++;
}
//returns the length
int side_pile::getlength() {
	return length;
}
