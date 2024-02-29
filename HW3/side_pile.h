#pragma once
class side_pile {
private:
	int pile[5];
	int length=0;
public:
	void add(int card);
	int play();
	int getlength();
};
