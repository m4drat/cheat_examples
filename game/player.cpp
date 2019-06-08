#include "player.h"

Player::Player() 
{
	healStats->health = 10;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;

	damageStats->damage = 2;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;

	handle = "none";
}

Player::Player(std::string name, int healt, int damage)
{
	healStats->health = healt;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;

	damageStats->damage = damage;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;

	handle = name;
}

Player::~Player() 
{

}

int Player::decrease_health(int dmg) 
{
	return 0;
}

void Player::die() {
}

int Player::attack(Unit *unit) {
	return 0;
}

int Player::heal(Unit *unit) {
	return 0;
}