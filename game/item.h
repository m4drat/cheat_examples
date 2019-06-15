#pragma once

#include "gameobject.h"

class Item : public GameObject
{
protected:
	std::string desc;
public:
	enum Rarity
	{
		none,
		common,
		rare,
		epic,
		legendary,
		last
	};
	Item::Rarity rarity;

	std::string get_desc();
	Item::Rarity get_rarity();
	std::string get_rarity_str();

	virtual ~Item();
};