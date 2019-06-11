#pragma once

#include "game.h"
#include "item.h"
#include "unit.h"

class Potion : public Item
{
public:
	Potion();
	~Potion();
	virtual void use(Unit *unit) = 0;
};