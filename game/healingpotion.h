#pragma once

#include "potion.h"

class HealPotion : public Potion
{
protected:
	int healval;
public:
	HealPotion();
	~HealPotion();
	void use(Unit *unit);
};