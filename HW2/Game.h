#pragma once
class wheel {
private:
	int wheel_size;
public:
	wheel();
	int spin();
	int get_wheel_size();
	void set_wheel_size(int s);
};
class player {
private:
	int cash;
public:
	player();
	player(int money,wheel playerWheel );
	wheel pWheel;
	int get_cash();
	void set_cash();
};
