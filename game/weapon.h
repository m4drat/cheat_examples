#pragma once

#include "item.h"

class Weapon : public Item
{
protected:
	int damage;
public:
	enum WeaponType
	{
		none,
		sword,
		bow,
		last
	};
	WeaponType weaponType;

	Weapon::WeaponType get_type();
	std::string get_type_str();
	int get_damage();
	static WeaponType random_weapon();
};