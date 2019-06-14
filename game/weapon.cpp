#include "weapon.h"

Weapon::WeaponType Weapon::random_weapon()
{
	return static_cast<Weapon::WeaponType>(rand() % Weapon::WeaponType::last);
}

int Weapon::get_damage()
{
	return damage;
}

Weapon::WeaponType Weapon::get_type()
{
	return weaponType;
}

std::string Weapon::get_type_str()
{
	switch (weaponType)
	{
	case Weapon::WeaponType::bow:
		return "bow";
	case Weapon::WeaponType::sword:
		return "sword";
	default:
		return "none";
	}
}