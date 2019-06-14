#include "bow.h"

Bow::Bow()
{
	desc = "Simple Bow";

	weaponType = WeaponType::bow;

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

Bow::~Bow()
{
}
