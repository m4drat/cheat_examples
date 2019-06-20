#pragma once

#include "item.h"
#include "unit.h"

class Potion : public Item
{
public:
	enum PotionType
	{
		none,
		heal,
		last
	};
	PotionType potionType;

	Potion();
	~Potion();
	virtual int use(Unit *unit);

	Potion::PotionType get_type() {};
};