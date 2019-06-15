#include "unit.h"
#include "bow.h"
#include "sword.h"
#include "healingpotion.h"

Unit::Unit() { // Constructor
	healStats = new HealStats;
	damageStats = new DamageStats;
}

Unit::~Unit() { // Destructor
	delete healStats;
	delete damageStats;

	for (int i = 0; i < items.size(); ++i)
	{
		if (items[i] != NULL)
			delete items[i];
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
		if (activeItem != NULL)
		{
			if (Bow* bow = dynamic_cast<Bow *>(activeItem)) {
				return damageStats->damage + bow->get_damage();
			}
			else if (Sword* sword = dynamic_cast<Sword *>(activeItem))
			{
				return damageStats->damage + sword->get_damage();
			}
		}
		return damageStats->damage;
	}
	return NULL;
}

bool Unit::get_isAlive()
{
	return isAlive;
}

std::vector <Item *>* Unit::get_inventory()
{
	return &items;
}

Item* Unit::get_active_item()
{
	if (activeItem != NULL)
		return activeItem;
	return NULL;
}