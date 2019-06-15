#include "unit.h"
#include "bow.h"
#include "sword.h"

class Enemy : public Unit
{
protected:
	struct Reward
	{
		int minGoldReward;
		int maxGoldReward;
		int minExpReward;
		int maxExpReward;
		int gold;
		int exp;
	};

	Reward *reward;

	std::vector <std::string> enemies = { "skelet", "goblin", "gul'", "zombie", "ogr" };

	void init();

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

	int get_gold();
	int get_exp();
};