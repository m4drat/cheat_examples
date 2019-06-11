#pragma once

#include "weapon.h"

class Sword : public Weapon
{
protected:
	void use();
public:
	Sword();
	~Sword();
};