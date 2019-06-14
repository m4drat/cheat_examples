#pragma once

#include "potion.h"
//#include "unit.h"

class HealPotion : public Potion
{
protected:
	int healval;
public:
	HealPotion();
	~HealPotion();
	void use(Unit *unit);
};