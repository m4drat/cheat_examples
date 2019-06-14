#include "sword.h"

Sword::Sword()
{
	desc = "Simple Sword";

	weaponType = WeaponType::sword;

	int minDamage = 1;
	int maxDamage = 10;
	damage = rand() % maxDamage + minDamage;

	if (damage >= 1 && damage <= 3)
		rarity = Rarity::common;
	else if (damage >= 4 && damage <= 6)
		rarity = Rarity::rare;
	else if (damage >= 4 && damage <= 6)
		rarity = Rarity::rare;
	else if (damage >= 7 && damage <= 9)
		rarity = Rarity::epic;
	else if (damage == 10)
		rarity = Rarity::legendary;
}

Sword::~Sword()
{
}