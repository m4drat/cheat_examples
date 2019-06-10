#include "game.h"
#include "player.h"
#include "enemy.h"

void update() {
	srand(time(NULL));
}

int main(int argc, char *argv[])
{
	std::string choice = "";

	Enemy *enemy = NULL;
	Player *player = NULL;
	
	for (;;) {
		update();

		std::cout << "[+] create - crete new Player with random stats\n";
		std::cout << "[+] fight - with random enemy\n";
		std::cout << "[+] stats - view your stats\n";
		std::cout << "> ";
		std::cin >> choice;

		if (choice == "create") {
			std::string name;
			std::cout << "[*] Enter player name: ";
			std::cin >> name;
			player = new Player(name);
			if (player != NULL) {
				std::cout << "[*] Player created!\n";
				std::cout << "[*] Your stats\n";
				std::cout << "[*]     Handle: " + player->get_handle() + "\n";
				std::cout << "[*]     Health: " + std::to_string(player->get_health()) + "\n";
				std::cout << "[*]     Heal:   " + std::to_string(player->get_heal()) + "\n";
				std::cout << "[*]     Damage: " + std::to_string(player->get_damage()) + "\n";
				std::cout << "[*]     Gold: " + std::to_string(player->get_gold()) + "\n";
				std::cout << "[*]     Exp: " + std::to_string(player->get_exp()) + "\n\n";
			}
			else {
				std::cout << "[-] Something went horribly wrong...\n";
			}
		}
		else if (choice == "fight") {
			if (player != NULL) {
				enemy = new Enemy();
				if (enemy != NULL) {
					std::cout << "[*] Enemy stats\n";
					std::cout << "[*]     Handle: " + enemy->get_handle() + "\n";
					std::cout << "[*]     Health: " + std::to_string(enemy->get_health()) + "\n";
					std::cout << "[*]     Heal:   " + std::to_string(enemy->get_heal()) + "\n";
					std::cout << "[*]     Damage: " + std::to_string(enemy->get_damage()) + "\n";
					std::cout << "[*]     Gold:   " + std::to_string(enemy->get_gold()) + "\n";
					std::cout << "[*]     Exp:    " + std::to_string(enemy->get_exp()) + "\n";

					// While hp of enemy and player isnt null
					while (player->get_health() != 0 && enemy->get_health() != 0)
					{
						std::cout << "[*] Write 'a' to attack\n";
						std::cout << "[*] Write 'h' to heal\n";
						std::cout << "[*] Write 'r' to run away (you will lose exp and gold)\n> ";
						std::cin >> choice;
						if (choice == "a" || choice == "attack") {
							player->attack(enemy);
							std::cout << "[+] You have dealt " + std::to_string(player->get_damage()) + " damage\n";
							std::cout << "[+] Enemy health: " + std::to_string(enemy->get_health()) + "\n";

							if (enemy->get_health() != 0)
							{
								std::cout << "[*] Enemy attacking you\n";
								enemy->attack(player);
								std::cout << "[+] You were dealt " + std::to_string(enemy->get_damage()) + " points of damage\n";
								std::cout << "[+] Your health: " + std::to_string(player->get_health()) + "\n\n";
							}
						}
						else if (choice == "h" || choice == "heal")
						{
							player->heal(player);
							std::cout << "[+] You cured yourself for " + std::to_string(player->get_heal()) + " hitpoints\n";
							std::cout << "[+] Your hp: " + std::to_string(player->get_health()) + "\n";

							std::cout << "[*] Enemy attacking you\n";
							enemy->attack(player);
							std::cout << "[+] You were dealt " + std::to_string(enemy->get_damage()) + " points of damage\n";
							std::cout << "[+] Your health: " + std::to_string(player->get_health()) + "\n\n";
						}
						else if (choice == "r" || choice == "run")
						{
							player->decrease_gold(enemy->get_gold());
							player->decrease_exp(enemy->get_exp());

							std::cout << "[-] You are running away!\n";
							std::cout << "[+] You lost " + std::to_string(enemy->get_gold()) + " gold\n";
							std::cout << "[+] You lost " + std::to_string(enemy->get_exp()) + " exp\n\n";
							break;
						}
					}
					if (player->get_health() == 0) {
						std::cout << "[-] You died\n";
						player = NULL;
					}
					else if (enemy->get_health() == 0) {
						player->increase_gold(enemy->get_gold());
						player->increase_exp(enemy->get_exp());
						std::cout << "[+] You got\n";
						std::cout << "[+]    Gold: " + std::to_string(enemy->get_gold()) + "\n";
						std::cout << "[+]    Exp:  " + std::to_string(enemy->get_exp()) + "\n";
						std::cout << "[+] You win\n\n";
					}
					delete enemy;
					enemy = NULL;
				}
				else {
					std::cout << "[-] Cannot create enemy\n";
				}
			}
			else {
				std::cout << "Player is NULL\n\n";
			}
		}
		else if (choice == "stats")
		{
			if (player != NULL)
			{
				std::cout << "[*] Your stats\n";
				std::cout << "[*]     Handle: " + player->get_handle() + "\n";
				std::cout << "[*]     Health: " + std::to_string(player->get_health()) + "\n";
				std::cout << "[*]     Heal:   " + std::to_string(player->get_heal()) + "\n";
				std::cout << "[*]     Damage: " + std::to_string(player->get_damage()) + "\n";
				std::cout << "[*]     Gold: " + std::to_string(player->get_gold()) + "\n";
				std::cout << "[*]     Exp: " + std::to_string(player->get_exp()) + "\n\n";
			}
			else {
				std::cout << "[-] Player is NULL\n";
			}
		}
	}

	return 0;
}