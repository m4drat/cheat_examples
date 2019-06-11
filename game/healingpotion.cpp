#include "healingpotion.h"

HealPotion::HealPotion()
{
	healval = 5;
}

HealPotion::~HealPotion()
{

}

void HealPotion::use(Unit *unit)
{
	unit->heal(unit, healval);
}