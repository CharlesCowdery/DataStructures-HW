#pragma once
class side_pile {
private:
	//private member variables
	int pile[5];
	int length=0;
public:
	//declaring side pile functions
	side_pile();
	~side_pile();
	void add(int card);
	int play();
	int getlength();
};
