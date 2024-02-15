#include "game.h"
#include <random>
using namespace std;
Wheel::Wheel() {
	wheel_size = 10; //init to default size

}
Wheel::Wheel(int size) {
	wheel_size = size;
}
int Wheel::spin() { //returns a random number in an inclusive range of the wheel
	return rand() % wheel_size + 1; //inclusive range
}
int Wheel::get_wheel_size() { //setters and getters for size
	return wheel_size;
}
void Wheel::set_wheel_size(int size) {
	wheel_size = size;
}

Player::Player(float _money, Wheel playerWheel) : cash(_money), pWheel(playerWheel) {}
Player::Player() : Player(0, Wheel()) {}
float Player::get_cash() { return cash; }
void Player::set_cash(float v) { cash = v; }