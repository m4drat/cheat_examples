#pragma once

#include "game.h"
#include "item.h"

class Potion : public Item
{
protected:
	void use();
public:
	Potion();
	~Potion();
};