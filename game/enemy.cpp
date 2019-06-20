#include "enemy.h"

Enemy::Enemy() // generate random enemy with random item
{
	init();

	if (rand() % 2 == 0) // generate heal potion
	{
		activeItem = new HealPotion();
	}
	else { // generate weapon
		switch (Weapon::random_weapon())
		{
		case Weapon::WeaponType::bow:
			activeItem = new Bow();
			break;
		case Weapon::WeaponType::sword:
			activeItem = new Sword();
			break;
		}
	}
	

	int minHealthRandom = 8;
	int maxHealthRandom = 30;

	isAlive = true;
	handle = enemies[rand() % 5];

	healStats->maxHealth = 40;
	healStats->minHealth = 0;
	healStats->health = rand() % maxHealthRandom + minHealthRandom;

	healStats->heal = 3;
	healStats->maxHeal = 5;

	int minDamageRandom = 1;
	int maxDamageRandom = 5;
	damageStats->maxDamage = 6;
	damageStats->minDamage = 1;
	damageStats->damage = rand() % maxDamageRandom + minDamageRandom;
}

Enemy::Enemy(std::string name, int health, int damage)
{
	init();

	activeItem = nullptr;

	isAlive = true;
	handle = name;

	healStats->health = health;
	healStats->maxHealth = 40;
	healStats->minHealth = 0;
	healStats->heal = 1;
	healStats->maxHeal = 2;

	damageStats->damage = damage;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;
}

Enemy::Enemy(std::string name, int health, int maxHealth, int minHealth, int heal, int maxHeal, int maxDamage, int minDamage, int damage)
{
	init();

	activeItem = nullptr;

	isAlive = true;
	handle = name;

	healStats->health = health;
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
	 if (activeItem != nullptr)
		 delete activeItem;
	delete reward;
}

int Enemy::decrease_health(int dmg)
{
	if (healStats != nullptr) {
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
	if (healStats != nullptr)
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
	if (unit != nullptr)
	{
		if (activeItem != nullptr)
		{
			if (Weapon* weapon = dynamic_cast<Weapon *>(activeItem)) // If object is typeof weapon
				unit->decrease_health(damageStats->damage + weapon->get_damage());
			else
				unit->decrease_health(damageStats->damage);
		} 
		else {
			unit->decrease_health(damageStats->damage);
		}
		return unit->get_health();
	}
	return NULL;
}

int Enemy::attack(Unit *unit, int dmg)
{
	if (unit != nullptr)
	{
		if (activeItem != nullptr)
			if (Weapon* weapon = dynamic_cast<Weapon *>(activeItem)) // If object is typeof weapon
			{
				unit->decrease_health(dmg + weapon->get_damage());
			}
			else {
				unit->decrease_health(dmg);
			}
		else
			unit->decrease_health(dmg);

		return unit->get_health();
	}
	return NULL;
}

int Enemy::heal(Unit *unit)
{
	if (unit != nullptr)
	{
		unit->increase_health(healStats->heal);
		return unit->get_health();
	}
	return NULL;
}

int Enemy::heal(Unit *unit, int healAmount)
{
	if (unit != nullptr)
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
	if (reward != nullptr) {
		return reward->gold;
	}
	return NULL;
}

int Enemy::get_exp()
{
	if (reward != nullptr) {
		return reward->exp;
	}
	return NULL;
}