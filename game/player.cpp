#include "player.h"

Player::Player() 
{
	init();

	isAlive = true;
	handle = "player";

	healStats->health = 10;
	healStats->maxHealth = 40;
	healStats->minHealth = 0;

	healStats->heal = 1;
	healStats->maxHeal = 2;

	damageStats->damage = 2;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;
}

Player::Player(std::string name)
{
	init();

	isAlive = true;
	handle = name;

	healStats->health = 22;
	healStats->maxHealth = 40;
	healStats->minHealth = 0;
	healStats->heal = 1;
	healStats->maxHeal = 5;

	damageStats->damage = 4;
	damageStats->maxDamage = 7;
	damageStats->minDamage = 1;
}

Player::Player(std::string name, int healt, int damage)
{
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

Player::Player(std::string name, int healt, int maxHealth, int minHealth, int heal, int maxHeal, int maxDamage, int minDamage, int damage)
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

Player::~Player()
{
}

void Player::init()
{
	if (properties == NULL)
	{
		properties = new Properties;
		properties->exp = 0;
		properties->gold = 0;
	}
}

int Player::increase_gold(int gold)
{
	if (properties != NULL)
	{
		try
		{
			if (gold < 0)
				throw NegativeGoldException();
		}
		catch (NegativeGoldException &e) {
			std::cout << e.what();
			return NULL;
		}
		properties->gold += gold;
		return properties->gold;
	}
	return NULL;
}

int Player::increase_exp(int exp)
{
	if (properties != NULL)
	{
		try
		{
			if (exp < 0)
				throw NegativeExpException();
		}
		catch (NegativeExpException &e) {
			std::cout << e.what();
			return NULL;
		}
		properties->exp += exp;
		return properties->exp;
	}
	return NULL;
}

int Player::decrease_gold(int gold)
{
	if (properties != NULL)
	{
		try
		{
			if (gold < 0)
				throw NegativeGoldException();
		}
		catch (NegativeGoldException &e) {
			std::cout << e.what();
			return NULL;
		}
		properties->gold -= gold;
		if (properties->gold < 0)
			properties->gold = 0;
		return properties->gold;
	}
	return NULL;
}

int Player::decrease_exp(int exp)
{
	if (properties != NULL)
	{
		try
		{
			if (exp < 0)
				throw NegativeExpException();
		}
		catch (NegativeExpException &e) {
			std::cout << e.what();
			return NULL;
		}
		properties->exp -= exp;
		if (properties->exp < 0)
			properties->exp = 0;
		return properties->exp;
	}
	return NULL;
}

int Player::decrease_health(int dmg)
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


int Player::increase_health(int heal) 
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

int Player::attack(Unit *unit) 
{
	if (unit != NULL) 
	{
		unit->decrease_health(damageStats->damage);
		return unit->get_health();
	}
	return NULL;
}

int Player::attack(Unit *unit, int dmg)
{
	if (unit != NULL)
	{
		unit->decrease_health(dmg);
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

int Player::heal(Unit *unit, int healAmount)
{
	if (unit != NULL)
	{
		unit->increase_health(healAmount);
		return unit->get_health();
	}
	return NULL;
}

int Player::equip(Item *item)
{
	items.push_back(item);
	return 0;
}

void Player::die() 
{
	isAlive = false;
}

int Player::get_gold()
{
	if (properties != NULL)
	{
		return properties->gold;
	}
	return NULL;
}

int Player::get_exp()
{
	if (properties != NULL)
	{
		return properties->exp;
	}
	return NULL;
}
