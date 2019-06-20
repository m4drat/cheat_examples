#pragma once

#include "potion.h"

class HealPotion : public Potion
{
protected:
	int healval;
public:
	HealPotion();
	~HealPotion();
	int use(Unit *unit);
	int get_heal_val();
};