#include "Game.h"
#include <random>
using namespace std;
Wheel::Wheel() {
	wheel_size = 10;

}
Wheel::Wheel(int size) {
	wheel_size = size;
}
int Wheel::spin() {
	return rand() % wheel_size + 1;
}
int Wheel::get_wheel_size() {
	return wheel_size;
}
void Wheel::set_wheel_size(int size) {
	wheel_size = size;
}

Player(int _money, Wheel playerWheel) : money(_money), pWheel(playerWheel)
Player() : Player(0, Wheel()) {}
int Player::get_cash() { return cash; }
void Player::set_cash(int v) { cash = v; }
