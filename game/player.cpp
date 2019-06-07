#include "player.h"

Player::Player() 
{
	healStats = new HealStats;
	healStats->health = 10;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;

	damageStats = new DamageStats;
	damageStats->damage = 2;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;

	handle = "none";
}

Player::Player(std::string name, int healt, int damage)
{
	healStats = new HealStats;
	healStats->health = healt;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;

	damageStats = new DamageStats;
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

std::string Player::get_handle()
{
	return handle;
}

int Player::get_health()
{
	return healStats->health;
}
int Player::get_damage()
{
	return damageStats->damage;
}