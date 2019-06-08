#include "player.h"

Player::Player() 
{
	healStats->health = 10;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;
	healStats->heal = 1;
	healStats->maxHeal = 2;

	damageStats->damage = 2;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;

	handle = "player";
}

Player::Player(std::string name, int healt, int damage)
{
	healStats->health = healt;
	healStats->maxHealt = 40;
	healStats->minHealh = 0;
	healStats->heal = 1;
	healStats->maxHeal = 2;

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
	if (healStats != NULL) {
		if (healStats->health <= healStats->minHealh)
		{
			healStats->health = 0;
			die();
			return healStats->health;
		}
		healStats->health -= dmg;
		return healStats->health;
	}
	return NULL;
}


int Player::increase_health(int heal) 
{
	if (healStats != NULL) 
	{
		healStats->health += heal;
		return healStats->health;
	}
	return NULL;
}

int Player::attack(Unit *unit) 
{
	if (unit != NULL) 
	{
		unit->decrease_health(damageStats->damage);
		return unit->get_health();
	}
	return NULL;
}

int Player::heal(Unit *unit)
{
	if (unit != NULL) 
	{
		unit->increase_health(healStats->heal);
		return unit->get_health();
	}
	return NULL;
}

void Player::die() 
{
	std::cout << "Player died\n";
}