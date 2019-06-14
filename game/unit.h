#pragma once

#include "gameobject.h"

class Unit : public GameObject
{
protected:
	struct HealStats
	{
		int health;
		int maxHealth;
		int minHealth;
		int heal;
		int maxHeal;
	};
	
	struct DamageStats
	{
		int damage;
		int maxDamage;
		int minDamage;
	};

	HealStats *healStats = NULL;
	DamageStats *damageStats = NULL;
	std::string handle;
	bool isAlive;

	std::vector <Weapon *> weapons; // all weapons
	std::vector <Potion *> potions; // all potions
	Weapon *activeWeapon = NULL; // currently avtive item

public:
	Unit();
	~Unit();

	virtual int decrease_health(int dmg) = 0; // damage yourself
	virtual int increase_health(int heal) = 0;
	virtual int attack(Unit *unit) = 0; // use unit default damage value
	virtual int attack(Unit *unit, int dmg) = 0;
	virtual int heal(Unit *unit) = 0; // use unit default heal value
	virtual int heal(Unit *unit, int healAmount) = 0;
	virtual void die(void) = 0;

	std::string get_handle();
	int get_health();
	int get_heal();
	int get_damage();
	bool get_isAlive();
	// std::vector <Item *>* get_inventory();
	Weapon* get_active_weapon();
};