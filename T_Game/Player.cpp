#include "Player.h"

Player::Player()
{
	_x = 0;
	_y = 0;
}

void Player::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;

}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}


void Player::getPosition(int& x, int& y) {
	x = _x;
	y = _y;

}

int Player::attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(0, _attack);
	return attackRoll(randomEngine);
}

void Player::addExperience(int experience) {

	_experience += experience;
	//level up
	while (_experience > 50) {
		printf("leveled up!\n");
		_experience -= 50;
		_attack += 10;
		_defense += 5;
		_health += 10;
		_level++;
		//Bad Habit :/
		system("PAUSE");

	}
}

int Player::takeDamage(int attack) {
	attack -= _defense;
	//Check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		//Check if he died
		if (_health <= 0) {
			return 1;

		}

	}


	return 0;

}