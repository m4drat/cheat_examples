#include "game.h"
#include "player.h"
#include "enemy.h"

void show_banner() {
	std::string introBanner = R"EOF(        _
       (_)
       |=|
       |=|
   /|__|_|__|\
  (    ( )    )                Welcome to Emberstorm RPG!
   \|\/\"/\/|/              >>>>>-------------------------->
     |  Y  |
     |  |  |
     |  |  |
    _|  |  |
 __/ |  |  |\
/  \ |  |  |  \
   __|  |  |   |
/\/  |  |  |   |\
 <   +\ |  |\ />  \
  >   + \  | LJ    |
        + \|+  \  < \
  (O)      +    |    )
   |             \  /\ 
 ( | )   (o)      \/  )
_\\|//__( | )______)_/ 
        \\|//

)EOF";
	std::cout << introBanner;
}

void update() {
	srand(time(NULL));
}

int main(int argc, char *argv[])
{
	std::string choice = "";

	Enemy *enemy = NULL;
	Player *player = NULL;
	
	show_banner();

	for (;;) {
		update();

		std::cout << "* [c]reate - crete new Player with random stats\n";
		std::cout << "* [f]ight  - with random enemy\n";
		std::cout << "* [s]tats  - view your stats\n";
		std::cout << "* [e]xit   - leave game\n";
		std::cout << "> ";
		std::cin >> choice;
		std::cout << '\n';

		if (choice == "create" || choice == "c") {
			std::string name;
			std::cout << "[*] Enter player name: ";
			std::cin >> name;
			std::cout << '\n';

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
		else if (choice == "fight" || choice == "f") {
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
					while (player->get_isAlive() && enemy->get_isAlive())
					{
						std::cout << "* Write [a]ttack to attack enemy\n";
						std::cout << "* Write [h]eal to heal yourself\n";
						std::cout << "* Write [r]un away to run away (you will lose exp and gold)\n> ";
						std::cin >> choice;
						std::cout << '\n';

						if (choice == "a" || choice == "attack") {
							player->attack(enemy);
							std::cout << "[+] You have dealt " + std::to_string(player->get_damage()) + " damage\n";
							std::cout << "[+] Enemy health: " + std::to_string(enemy->get_health()) + "\n";

							if (enemy->get_isAlive())
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
					if (!player->get_isAlive()) {
						std::cout << "[-] You died\n";
						player = NULL;
					}
					else if (!enemy->get_isAlive()) {
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
		else if (choice == "stats" || choice == "s")
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
		else if (choice == "exit" || choice == "e") {
			std::cout << "Goodbye!\n";
			return 0;
		}
	}

	return 0;
}