#pragma once
class Wheel {
private:
	int wheel_size;
public:
	Wheel();
	Wheel(int size);
	int spin();
	int get_wheel_size();
	void set_wheel_size(int s);
};
class Player {
private:
	float cash;
public:
	Player();
	Player(float money, Wheel playerWheel);
	Wheel pWheel;
	float get_cash();
	void set_cash(float v);
};
