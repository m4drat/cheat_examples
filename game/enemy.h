#include "unit.h"

class Enemy : public Unit
{
public:
	Enemy(); // Default constructor
	Enemy(std::string name, int healt, int damage);
	Enemy(std::string name, int healt, int maxHealth, int minHealth, int heal, int maxHeal, int maxDamage, int minDamage, int damage);
	~Enemy();

	int decrease_health(int dmg);
	int increase_health(int heal);

	int attack(Unit *unit);
	int attack(Unit *unit, int dmg);

	int heal(Unit *unit);
	int heal(Unit *unit, int healAmount);

	void die();
};