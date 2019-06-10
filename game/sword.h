#pragma once

#include "game.h"
#include "item.h"

class Sword : public Item
{
protected:
	void use();
public:
	Sword();
	~Sword();
};