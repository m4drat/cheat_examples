#include "unit.h"

class Enemy : public Unit
{
public:
	Enemy(); // Default constructor
	Enemy(std::string name, int healt, int damage);
	~Enemy();

	int decrease_health(int dmg);
	int increase_health(int heal);
	int attack(Unit *unit);
	int heal(Unit *unit);
	void die();
};