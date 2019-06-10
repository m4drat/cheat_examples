#include "enemy.h"

Enemy::Enemy() // generate random enemy
{
	init();

	isAlive = true;
	handle = enemies[rand() % 5];

	healStats->maxHealth = 30;
	healStats->minHealth = 8;
	healStats->health = rand() % healStats->maxHealth + healStats->minHealth;

	healStats->heal = 3;
	healStats->maxHeal = 5;

	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;
	damageStats->damage = rand() % damageStats->maxDamage + damageStats->minDamage;
}

Enemy::Enemy(std::string name, int healt, int damage)
{
	init();

	isAlive = true;
	handle = name;

	healStats->health = healt;
	healStats->maxHealth = 40;
	healStats->minHealth = 0;
	healStats->heal = 1;
	healStats->maxHeal = 2;

	damageStats->damage = damage;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;
}

Enemy::Enemy(std::string name, int healt, int maxHealth, int minHealth, int heal, int maxHeal, int maxDamage, int minDamage, int damage)
{
	init();

	isAlive = true;
	handle = name;

	healStats->health = healt;
	healStats->maxHealth = maxHealth;
	healStats->minHealth = minHealth;
	healStats->heal = heal;
	healStats->maxHeal = maxHeal;

	damageStats->damage = damage;
	damageStats->maxDamage = maxDamage;
	damageStats->minDamage = minDamage;	
}

void Enemy::init() {
	reward = new Reward;

	reward->minGoldReward = 10;
	reward->maxGoldReward = 100;
	reward->minExpReward = 1;
	reward->maxExpReward = 5;
	reward->gold = rand() % reward->maxGoldReward + reward->minGoldReward;
	reward->exp = rand() % reward->maxExpReward + reward->minExpReward;
}

Enemy::~Enemy()
{
	delete reward;
}

int Enemy::decrease_health(int dmg)
{
	if (healStats != NULL) {
		try
		{
			if (dmg < 0)
				throw NegativeDamageException();
		}
		catch (NegativeDamageException &e) {
			std::cout << e.what();
			return NULL;
		}

		healStats->health -= dmg;
		if (healStats->health <= healStats->minHealth)
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
		try
		{
			if (heal < 0)
				throw NegativeHealException();
		}
		catch (NegativeHealException &e) {
			std::cout << e.what();
			return NULL;
		}

		healStats->health += heal;
		if (healStats->health > healStats->maxHealth)
			healStats->health = healStats->maxHealth;
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

int Enemy::attack(Unit *unit, int dmg)
{
	if (unit != NULL)
	{
		unit->decrease_health(dmg);
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

int Enemy::heal(Unit *unit, int healAmount)
{
	if (unit != NULL)
	{
		unit->increase_health(healAmount);
		return unit->get_health();
	}
	return NULL;
}

void Enemy::die() 
{
	isAlive = false;
}

int Enemy::get_gold()
{
	if (reward != NULL) {
		return reward->gold;
	}
	return NULL;
}

int Enemy::get_exp()
{
	if (reward != NULL) {
		return reward->exp;
	}
	return NULL;
}