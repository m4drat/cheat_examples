#include "unit.h"

class Enemy : public Unit
{
public:
	Enemy(); // Default constructor
	Enemy(std::string name, int healt, int damage);
	~Enemy();

	int decrease_health(int dmg);
	void die();
	int attack(Unit *unit);
	int heal(Unit *unit);
};