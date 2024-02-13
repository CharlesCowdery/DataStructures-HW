#include "game.h"
#include <iostream>

#include <iomanip>

using namespace std;
float spinning(Wheel house, string s,int spin_num) {
	int house_num1;
	int house_num2;
	if (s == "k") {
		house_num1 = house.spin();
		cout << "House spun:" << house_num1 << endl;
		if (spin_num > house_num1) return true;
		else return false;
	}
	else if (s == "d") {
		house_num1 = house.spin();
		cout << "House spun:" << house_num1 << endl;
		if (spin_num < house_num1) return false;
		house_num1 = house.spin();
		cout << "House spun:" << house_num1 << endl;
		if (spin_num < house_num1) return false;
		else return true;
	}
	else if (s == "d") {
		house_num1 = house.spin();
		cout << "House spun:" << house_num1 << endl;
		house_num2 = house.spin();
		cout << "House spun:" << house_num2 << endl;
		if (spin_num < house_num1 && spin_num<house_num2) return false;
		else return true;
	}

}
int play(Player &p,Wheel house_wheel) {
	float bet = 0;
	int spin_num;
	string type = "";
	cout<<"How much would you like to bet?"<<endl;
	cin >> bet;
	while (bet > p.get_cash()) {
		cout << "Invaild bet size reenter bet" << endl;
		cin >> bet;
	}
	spin_num = p.pWheel.spin();
	cout << "you spun a:" << spin_num << "would you like to keep(k) half(h) or double(d) your bet?" << endl;
	cin >> type;
	while (type != "k" && type != "h" && type != "d") {
		cout << "invalid input input k, h, or d";
		cin >> type;
	}
	if (type == "k") {
		bet = bet;
	}
	else if (type == "h") {
		bet = bet/2;
	}
	else {
		bet = bet * 2;
		if (bet > p.get_cash()) {
			cout << "Invaild reset to original bet" << endl;
			bet = bet / 2;
			type = "k";
		}
	}
	if (spinning(house_wheel, type, spin_num)) {
		cout << "congrats you won!" << endl;
		return bet;
	}
	else {
		cout << "you lost :(" << endl;
		return -bet;
	}
	
}