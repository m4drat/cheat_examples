#include "unit.h"

Unit::Unit() { // Constructor
	healStats = new HealStats;
	damageStats = new DamageStats;
}

Unit::~Unit() { // Destructor
	delete healStats;
	delete damageStats;

	for (int i = 0; i < weapons.size(); ++i)
	{
		if (weapons[i] != NULL)
			delete weapons[i];
	}
	
	for (int i = 0; i < potions.size(); ++i)
	{
		if (potions[i] != NULL)
			delete potions[i];
	}
}

std::string Unit::get_handle()
{
	return handle;
}

int Unit::get_health()
{
	if (healStats != NULL)
		return healStats->health;
	return NULL;
}

int Unit::get_heal()
{
	if (healStats != NULL)
		return healStats->heal;
	return NULL;
}

int Unit::get_damage()
{
	if (damageStats != NULL) {
		if (activeWeapon != NULL)
			return damageStats->damage + activeWeapon->get_damage();
		return damageStats->damage;
	}
	return NULL;
}

bool Unit::get_isAlive()
{
	return isAlive;
}

//std::vector <Item *>* Unit::get_inventory()
//{
//	return &weapons;
//}

Weapon* Unit::get_active_weapon()
{
	if (activeWeapon != NULL)
		return activeWeapon;
	return NULL;
}