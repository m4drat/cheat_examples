#include "enemy.h"

Enemy::Enemy()
{
	healStats->health = 10;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;

	damageStats->damage = 2;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;

	handle = "enemy";
}

Enemy::Enemy(std::string name, int healt, int damage)
{
	healStats->health = healt;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;

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
	if (healStats != NULL)
	{
		healStats->health -= dmg;
		if (healStats->health <= healStats->minHealh)
		{
			healStats->health = 0;
			die();
			return healStats->health;
		}
		return healStats->health;
	}
	return NULL;
}

int Enemy::increase_health(int heal)
{
	if (healStats != NULL)
	{
		healStats->health += heal;
		return healStats->health;
	}
	return NULL;
}

int Enemy::attack(Unit *unit) 
{
	if (unit != NULL)
	{
		unit->decrease_health(damageStats->damage);
		return unit->get_health();
	}
	return NULL;
}

int Enemy::heal(Unit *unit)
{
	if (unit != NULL) 
	{
		unit->increase_health(healStats->heal);
		return unit->get_health();
	}
	return NULL;
}

void Enemy::die() {
	std::cout << "Enemy died\n";
}