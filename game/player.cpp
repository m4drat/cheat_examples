#include "player.h"

Player::Player() 
{
	init();

	isAlive = true;
	handle = "player";

	healStats->health = 63;
	healStats->maxHealth = 80;
	healStats->minHealth = 0;

	healStats->heal = 0;
	healStats->maxHeal = 0;

	damageStats->damage = 2;
	damageStats->maxDamage = 5;
	damageStats->minDamage = 1;
}

Player::Player(std::string name)
{
	init();

	isAlive = true;
	handle = name;

	healStats->health = 63;
	healStats->maxHealth = 80;
	healStats->minHealth = 0;
	healStats->heal = 0;
	healStats->maxHeal = 0;

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
	healStats->heal = 0;
	healStats->maxHeal = 0;

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
	if (properties == nullptr)
	{
		properties = new Properties;
		properties->exp = 0;
		properties->gold = 0;
	}
}

int Player::increase_gold(int gold)
{
	if (properties != nullptr)
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
	if (properties != nullptr)
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
	if (properties != nullptr)
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
	if (properties != nullptr)
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

int Player::increase_total_killed()
{
	if (properties != nullptr)
	{
		properties->toltalKilled++;
		return properties->toltalKilled;
	}
	return NULL;
}

int Player::decrease_health(int dmg)
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


int Player::increase_health(int heal) 
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

int Player::attack(Unit *unit) 
{
	if (unit != nullptr)
	{
		if (activeItem != nullptr)
		{
			if (Bow* bow = dynamic_cast<Bow *>(activeItem)) {
				unit->decrease_health(damageStats->damage + bow->get_damage());
			}
			else if (Sword* sword = dynamic_cast<Sword *>(activeItem))
			{
				unit->decrease_health(damageStats->damage + sword->get_damage());
			}
			else {
				unit->decrease_health(damageStats->damage);
			}
		}
		else
			unit->decrease_health(damageStats->damage);

		return unit->get_health();
	}
	return NULL;
}

int Player::attack(Unit *unit, int dmg)
{
	if (unit != nullptr)
	{
		if (activeItem != nullptr)
		{
			if (Bow* bow = dynamic_cast<Bow *>(activeItem)) {
				unit->decrease_health(dmg + bow->get_damage());
			}
			else if (Sword* sword = dynamic_cast<Sword *>(activeItem))
			{
				unit->decrease_health(dmg + sword->get_damage());
			}
			else {
				unit->decrease_health(dmg);
			}
		}
		else
			unit->decrease_health(dmg);
		
		return unit->get_health();
	}
	return NULL;
}

int Player::heal(Unit *unit)
{
	if (unit != nullptr)
	{
		unit->increase_health(healStats->heal);
		return unit->get_health();
	}
	return NULL;
}

int Player::heal(Unit *unit, int healAmount)
{
	if (unit != nullptr)
	{
		unit->increase_health(healAmount);
		return unit->get_health();
	}
	return NULL;
}

size_t Player::lift_item(Item *item)
{
	if (Bow* bow = dynamic_cast<Bow *>(item)) {
		items.push_back(new Bow(*bow));
	}
	else if (Sword* sword = dynamic_cast<Sword *>(item))
	{
		items.push_back(new Sword(*sword));
	}
	else if (HealPotion* healPotion = dynamic_cast<HealPotion *>(item))
	{
		items.push_back(new HealPotion(*healPotion));
	}
	return items.size();
}

void Player::equip(Item *item)
{
	if (Bow* bow = dynamic_cast<Bow *>(item))
	{
		activeItem = bow; // Should i create here new Bow? Or I can reuse old one?
	}
	else if (Sword* sword = dynamic_cast<Sword *>(item))
	{
		activeItem = sword;
	}
}

void Player::die() 
{
	isAlive = false;
}

int Player::get_gold()
{
	if (properties != nullptr)
	{
		return properties->gold;
	}
	return NULL;
}

int Player::get_exp()
{
	if (properties != nullptr)
	{
		return properties->exp;
	}
	return NULL;
}

int Player::get_total_killed()
{
	if (properties != nullptr)
	{
		return properties->toltalKilled;
	}
	return NULL;
}
