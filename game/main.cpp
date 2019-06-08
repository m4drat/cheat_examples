#include "game.h"

#include "player.h"
#include "enemy.h"

int main(int argc, char *argv[])
{
	Player *player = new Player("madrat", 40, 3);
	Enemy *enemy = new Enemy("goblin", 10, 1);
	std::cout << player->attack(enemy) << '\n';
	std::cout << player->heal(enemy, -2);
	return 0;
}