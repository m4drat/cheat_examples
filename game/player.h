#include "unit.h"

class Player : public Unit
{
public:
	Player(); // Default constructor
	Player(std::string name, int healt, int damage);
	~Player();

	int decrease_health(int dmg);
	int increase_health(int heal);
	int attack(Unit *unit);
	int heal(Unit *unit);
	void die();
};