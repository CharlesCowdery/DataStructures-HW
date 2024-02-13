Player(int _money, Wheel playerWheel) : money(_money), pWheel(playerWheel)
Player() :Player(0, Wheel()) {}
int Player::get_cash() { return cash; }
void Player::set_cash(int v) { cash = v; }
