#pragma once
class Wheel {
private:
	int wheel_size;
public:
	Wheel();
	int spin();
	int get_wheel_size();
	void set_wheel_size(int s);
};
class Player {
private:
	int cash;
public:
	Player();
	Player(int money,Wheel playerWheel );
	Wheel pWheel;
	int get_cash();
	void set_cash();
};
