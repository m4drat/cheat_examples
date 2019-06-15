#include "healingpotion.h"

HealPotion::HealPotion()
{
	desc = "Simple Heal Potion";

	int minHealVal = 1;
	int maxHealVal = 9;
	healval = rand() % maxHealVal + minHealVal;

	if (healval >= 1 && healval <= 2)
		rarity = Rarity::common;
	else if (healval >= 3 && healval <= 4)
		rarity = Rarity::rare;
	else if (healval >= 5 && healval <= 6)
		rarity = Rarity::rare;
	else if (healval >= 7 && healval <= 8)
		rarity = Rarity::epic;
	else if (healval == 9)
		rarity = Rarity::legendary;
}

HealPotion::~HealPotion()
{
}

void HealPotion::use(Unit *unit)
{
	unit->heal(unit, healval);
}

int HealPotion::get_heal_val()
{
	return healval;
}