#include "unit.h"
#include "bow.h"
#include "sword.h"
#include "healingpotion.h"

class Player : public Unit
{
protected:
	struct Properties
	{
		int gold = 0;
		int exp = 0;
	};
	Properties *properties = NULL;

public:
	Player(); // Default constructor
	Player(std::string name);
	Player(std::string name, int healt, int damage);
	Player(std::string name, int healt, int maxHealth, int minHealth, int heal, int maxHeal, int maxDamage, int minDamage, int damage);
	~Player();

	int increase_gold(int gold);
	int increase_exp(int exp);
	int decrease_gold(int gold);
	int decrease_exp(int exp);

	int decrease_health(int dmg);
	int increase_health(int heal);
	
	int attack(Unit *unit);
	int attack(Unit *unit, int dmg);
	
	int heal(Unit *unit);
	int heal(Unit *unit, int healAmount);

	size_t lift_item(Item *item); // add item to inventory
	void equip(Item *item); // equip weapon

	void die();
	void init();

	int get_gold();
	int get_exp();
};