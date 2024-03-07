#include "side_pile.h"
#include "side_pile_empty.h"
#include "side_pile_full.h"

side_pile::side_pile() {}
side_pile::~side_pile() {};
int side_pile::play() {
	if (length == 0) {
		throw StackEmpty();
	}
	length--;
	return pile[length];
}
void side_pile::add(int card) {
	if (length == 5) {
		throw StackFull();
	}
	pile[length] = card;
	length++;
}
int side_pile::getlength() {
	return length;
}
