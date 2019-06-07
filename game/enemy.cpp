#include "enemy.h"


Enemy::Enemy()
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

Enemy::Enemy(std::string name, int healt, int damage)
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

Enemy::~Enemy()
{

}

int Enemy::decrease_health(int dmg)
{
	return 0;
}

void Enemy::die() {
}

int Enemy::attack(Unit *unit) {
	return 0;
}

int Enemy::heal(Unit *unit) {
	return 0;
}

std::string Enemy::get_handle()
{
	return handle;
}

int Enemy::get_health()
{
	return healStats->health;
}
int Enemy::get_damage()
{
	return damageStats->damage;
}