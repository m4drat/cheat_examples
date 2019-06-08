#include "unit.h"

class Player : public Unit
{
public:
	Player(); // Default constructor
	Player(std::string name, int healt, int damage);
	Player(std::string name, int healt, int maxHealth, int minHealth, int heal, int maxHeal, int maxDamage, int minDamage, int damage);
	~Player();

	int decrease_health(int dmg);
	int increase_health(int heal);
	
	int attack(Unit *unit);
	int attack(Unit *unit, int dmg);
	
	int heal(Unit *unit);
	int heal(Unit *unit, int healAmount);

	void die();
};