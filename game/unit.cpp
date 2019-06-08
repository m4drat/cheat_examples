#include "unit.h"

Unit::Unit() { // Constructor
	healStats = new HealStats;
	damageStats = new DamageStats;
}

Unit::~Unit() { // Destructor
	delete healStats;
	delete damageStats;
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
	if (damageStats != NULL)
		return damageStats->damage;
	return NULL;
}