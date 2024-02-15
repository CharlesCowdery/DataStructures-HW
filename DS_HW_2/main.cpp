#include <iostream>

#include <time.h>
#include "game.h";
using namespace std;
float spinning(Wheel house, string s, int spin_num) {
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
		if (spin_num <= house_num1) return false;
		house_num1 = house.spin();
		cout << "House spun:" << house_num1 << endl;
		if (spin_num <= house_num1) return false;
		else return true;
	}
	else if (s == "h") {
		house_num1 = house.spin();
		cout << "House spun:" << house_num1 << endl;
		house_num2 = house.spin();
		cout << "House spun:" << house_num2 << endl;
		if (spin_num < house_num1 && spin_num < house_num2) return false;
		else return true;
	}

}
float play(Player& p, Wheel house_wheel,bool h) {
	static int loose=0;
	float bet = 0;
	int spin_num;
	string type = "";
	cout << "How much would you like to bet?" << endl;
	cin >> bet;
	while (bet > p.get_cash()) {
		cout << "Invaild bet size reenter bet" << endl;
		cin >> bet;
	}
	spin_num = p.pWheel.spin();
	cout << "you spun a: " << spin_num << endl<<"would you like to keep(k) half(h) or double(d) your bet?" << endl;
	cin >> type;
	while (type != "k" && type != "h" && type != "d") {
		cout << "invalid input input k, h, or d";
		cin >> type;
	}
	if (type == "k") {
		bet = bet;
	}
	else if (type == "h") {
		bet = bet / 2.0;
	}
	else if (type=="d") {
		bet = bet * 2;
		loose = 0;
		if (bet > p.get_cash()) {
			cout << "Invaild reset to original bet" << endl;
			bet = bet / 2;
			type = "k";
		}
	}
	if (spinning(house_wheel, type, spin_num)) {
		cout << "congrats you won! " << endl;
		loose = 0;
		if (h ) {
			
			cout << "house wheel increased by 1!" << endl;
			house_wheel.set_wheel_size(house_wheel.get_wheel_size() + 1);
			cout << "the house wheel is now:" <<house_wheel.get_wheel_size()<< endl;
		}
		return bet;
	}
	else {
		cout << "you lost :(" << endl;
		loose++;
		if (h && loose == 2) {
			loose = 0;
			cout << "house wheel decreased by 1!" << endl;
			house_wheel.set_wheel_size(house_wheel.get_wheel_size() - 1);
			cout << "the house wheel is now:" << house_wheel.get_wheel_size() << endl;
		}
		return -bet;
	}

}

int main() {
	//setting it to be random used:http://stackoverflow.com/a/16569330/13946283
	srand(time(NULL));
	float moneyCount = 0;
	int wheelSize = 0;
	string in;
	bool hard=false;
	cout << "Enter how much money you would like to start with: $";
	cin >> moneyCount;
	while (true) {
		cout << "choose the size of wheel youd like to play with [6-20]: " << flush;
		cin >> wheelSize;
		if (wheelSize < 6 || wheelSize > 20) cout << "Out of range." << endl;
		else break;
	}
	cout << "Would you like to play in hardmode?(y/n)";
	cin >> in;
	if (in == "y") {
		hard = true;
	}
	Wheel w(wheelSize);
	Player p(moneyCount, w);
	Wheel h(wheelSize);
	int opt = 0;

	while (p.get_cash() > 0&&!hard) {
		cout << "what would you like to do? 1: bet and play. 2:see money. 3: cashout." << endl;
		cin >> opt;
		while (opt < 1 || opt>3) {
			cout << "invalid input please do options 1 through 3:" << endl;
			cin >> opt;
		}
		if (opt == 1) {
			p.set_cash(p.get_cash() + play(p, h,hard));
			cout << "your new total cash is:" << p.get_cash()<<endl;
		}
		else if (opt == 2) {
			cout << "your total cash is:" << p.get_cash()<<endl;
		}
		else if(opt==3) {
			cout << "goodbye" << endl;
			return 1;
		}


	}
	while (p.get_cash() > 0 && hard) {
		int win = 0;
		cout << "what would you like to do? 1: bet and play. 2:see money. 3: cashout." << endl;
		cin >> opt;
		while (opt < 1 || opt>3) {
			cout << "invalid input please do options 1 through 3:" << endl;
			cin >> opt;
		}
		if (opt == 1) {
			p.set_cash(p.get_cash() + play(p, h,hard));
			cout << "your new total cash is:" << p.get_cash() << endl;
		}
		else if (opt == 2) {
			cout << "your total cash is:" << p.get_cash() << endl;
		}
		else if (opt == 3) {
			cout << "goodbye" << endl;
			return 1;
		}


	}
	cout << "you are out of cash goodbye.";

	return 1;
}