#include "unit.h"

class Player : public Unit
{
public:
	Player(); // Default constructor
	Player(std::string name, int healt, int damage);
	~Player();

	int decrease_health(int dmg);
	void die();
	int attack(Unit *unit);
	int heal(Unit *unit);
};