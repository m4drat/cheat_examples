#include "game.h"
#include "player.h"
#include "enemy.h"

int main(int argc, char *argv[])
{
	Player *player = new Player("madrat", 40, 3);
	std::cout << player->get_handle();
	return 0;
}