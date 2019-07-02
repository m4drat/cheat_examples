#pragma once

#include "item.h"

class Weapon : public Item
{
protected:
	int damage = 0;
public:
	enum WeaponType
	{
		none,
		sword,
		bow,
		last
	};
	Weapon::WeaponType weaponType = Weapon::WeaponType::none;

	Weapon::WeaponType get_type();
	std::string get_type_str();
	int get_damage();
	static Weapon::WeaponType random_weapon();
};