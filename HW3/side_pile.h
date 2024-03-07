#pragma once
class side_pile {
private:
	int pile[5];
	int length=0;
public:
	side_pile();
	~side_pile();
	void add(int card);
	int play();
	int getlength();
};
