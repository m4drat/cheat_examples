#include "game.h"
#include "player.h"
#include "enemy.h"

int main(int argc, char *argv[])
{
	std::string choice = "";

	Enemy *enemy = NULL;
	Player *player = NULL;
	
	show_banner();

	for (;;) {
		update();

		std::cout << "* [c]reate    - crete new Player with random stats\n";
		std::cout << "* [f]ight     - with random enemy\n";
		std::cout << "* [s]tats     - view your stats\n";
		std::cout << "* [i]nventory - view your inventory\n";
		std::cout << "* [e]xit      - leave game\n";
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
				std::cout << "[*]     Gold:   " + std::to_string(player->get_gold()) + "\n";
				std::cout << "[*]     Exp:    " + std::to_string(player->get_exp()) + "\n";
				std::cout << "[*]     Total Killed: " + std::to_string(player->get_total_killed()) + "\n\n";
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
					if (enemy->get_active_item() != NULL)
					{
						if (Weapon* weapon = dynamic_cast<Weapon *>(enemy->get_active_item())) // If object is typeof weapon
						{
							std::cout << "[*]     Damage: " + std::to_string(enemy->get_damage() - weapon->get_damage()) + " (+" + std::to_string(weapon->get_damage()) + ")" + "\n";
						}
						else {
							std::cout << "[*]     Damage: " + std::to_string(enemy->get_damage()) + "\n";
						}
					}
					else {
						std::cout << "[*]     Damage: " + std::to_string(enemy->get_damage()) + "\n";
					}
					std::cout << "[*]     Gold:   " + std::to_string(enemy->get_gold()) + "\n";
					std::cout << "[*]     Exp:    " + std::to_string(enemy->get_exp()) + "\n";

					if (enemy->get_active_item() != NULL)
					{
						if (Weapon* weapon = dynamic_cast<Weapon *>(enemy->get_active_item())) // If object is typeof weapon
						{
							std::cout << "[*] Enemy item: " + weapon->get_type_str() + "\n";
							std::cout << "[*]   Damage: " + std::to_string(weapon->get_damage()) + "\n";
						}
						else if (HealPotion* healPotion = dynamic_cast<HealPotion *>(enemy->get_active_item())) {
							std::cout << "[*] Enemy item: healing Potion\n";
							std::cout << "[*]   Heal:     " + std::to_string(healPotion->get_heal_val()) + "\n";
						}
						std::cout << "[*]   Rarity: " + enemy->get_active_item()->get_rarity_str() + "\n";
					}

					// While hp of enemy and player isnt null
					while (player->get_isAlive() && enemy->get_isAlive())
					{
						update();
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
							std::cout << "[+] Available healing potions:\n";
							int counter = 1;
							for (Item *item : *player->get_inventory())
							{
								if (HealPotion* healPotion = dynamic_cast<HealPotion *>(item))
								{
									std::cout << "---------- " + std::to_string(counter) + " ----------\n";
									std::cout << "[+] Heal:   " + std::to_string(healPotion->get_heal_val()) << "\n";
									std::cout << "[+] Desc:   " + healPotion->get_desc() << "\n";
									std::cout << "[+] Rarity: " + healPotion->get_rarity_str() << "\n";
								}
								counter++;
							}

							std::cout << "[+] Which one you want to use?\n> ";
							std::cin >> choice;

							if (std::stoi(choice) > 0 && std::stoi(choice) <= player->get_inventory()->size())
							{
								if ((*player->get_inventory())[std::stoi(choice) - 1] != NULL)
								{
									if (HealPotion* healPotion = dynamic_cast<HealPotion *>((*player->get_inventory())[std::stoi(choice) - 1]))
									{
										healPotion->use(player);
										std::cout << "[+] You cured yourself for " + std::to_string(healPotion->get_heal_val()) + " hitpoints\n";
										std::cout << "[+] Your hp: " + std::to_string(player->get_health()) + "\n";

										delete (*player->get_inventory())[std::stoi(choice) - 1];
										player->get_inventory()->erase(player->get_inventory()->begin() + std::stoi(choice) - 1);
									}
									else {
										std::cout << "[-] Not a potion\n";
									}
								}
							}
							else {
								std::cout << "[-] Cannot use this potion\n";
							}

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
						player->increase_total_killed();
						player->increase_gold(enemy->get_gold());
						player->increase_exp(enemy->get_exp());
						std::cout << "[+] You got\n";
						std::cout << "[+]    Gold: " + std::to_string(enemy->get_gold()) + "\n";
						std::cout << "[+]    Exp:  " + std::to_string(enemy->get_exp()) + "\n";

						if (enemy->get_active_item() != NULL)
						{
							if (Weapon* weapon = dynamic_cast<Weapon *>(enemy->get_active_item())) // If object is typeof weapon
							{
								std::cout << "[*] New item: " + weapon->get_type_str() + "\n";
								std::cout << "[*]   Damage: " + std::to_string(weapon->get_damage()) + "\n";
							}
							player->lift_item(enemy->get_active_item());
						}
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
				if (player->get_active_item() != NULL)
				{
					if (Weapon* weapon = dynamic_cast<Weapon *>(player->get_active_item())) // If object is typeof weapon
					{
						std::cout << "[*]     Damage: " + std::to_string(player->get_damage() - weapon->get_damage()) + " (+" + std::to_string(weapon->get_damage()) + ")" + "\n";
					}
					else {
						std::cout << "[*]     Damage: " + std::to_string(player->get_damage()) + "\n";
					}
				}
				else {
					std::cout << "[*]     Damage: " + std::to_string(player->get_damage()) + "\n";
				}
				std::cout << "[*]     Gold:   " + std::to_string(player->get_gold()) + "\n";
				std::cout << "[*]     Exp:    " + std::to_string(player->get_exp()) + "\n";
				std::cout << "[*]     Total Killed: " + std::to_string(player->get_total_killed()) + "\n\n";
			}
			else {
				std::cout << "[-] Player is NULL\n";
			}
		}
		else if (choice == "inventory" || choice == "i") // FIXME: I DONT KNOW HOW TO MAKE INVENTORY WORK!
		{
			if (player != NULL)
			{
				std::cout << "[d]isplay - display inventory\n";
				std::cout << "[e]quip   - equip new item\n> ";
				std::cin >> choice;
				std::cout << "\n";

				if (choice == "d" || choice == "display")
				{
					if (player->get_active_item() != NULL)
					{
						std::cout << "[+] Currently selected item\n";
						if (Weapon* weapon = dynamic_cast<Weapon *>(player->get_active_item()))
						{
							std::cout << "  * Type:   " + weapon->get_type_str() << "\n";
							std::cout << "  * Desc:   " + weapon->get_desc() + "\n";
							std::cout << "  * Damage: " + std::to_string(weapon->get_damage()) + "\n";
							std::cout << "  * Rarity: " + weapon->get_rarity_str() + "\n";
						}
					}
					else {
						std::cout << "[-] No item selected\n";
					}

					std::cout << "[*] Your inventory:\n";
					int counter = 1;
					if (player->get_inventory()->size() == 0)
					{
						std::cout << "  Inventory is empty\n";
					}

					for (Item *item : *(player->get_inventory()))
					{
						if (item != NULL)
						{
							std::cout << "---------- " + std::to_string(counter) + " ----------\n";
							if (Weapon* weapon = dynamic_cast<Weapon *>(item))
							{
								std::cout << "  * Item:   " + weapon->get_type_str() + "\n";
								std::cout << "  * Desc:   " + weapon->get_desc() + "\n";
								std::cout << "  * Damage: " + std::to_string(weapon->get_damage()) + "\n";
                                std::cout << "  * Rarity: " + weapon->get_rarity_str() + "\n";
							}
							else if (HealPotion* healPotion = dynamic_cast<HealPotion *>(item))
							{
								std::cout << "  * Item: healing potion\n";
								std::cout << "  * Desc:   " + healPotion->get_desc() + "\n";
								std::cout << "  * Heal:   " + std::to_string(healPotion->get_heal_val()) + "\n";
                                std::cout << "  * Rarity: " + healPotion->get_rarity_str() + "\n";
							}
						}
						counter++;
					}
					std::cout << "\n";
				}
				else if (choice == "e" || choice == "equip")
				{
					if (player->get_inventory()->size() != 0)
					{
						std::cout << "[+] Select item you want to pick up [1-" + std::to_string(player->get_inventory()->size()) + "]\n> ";
						std::cin >> choice;
						std::cout << "\n";
						if (std::stoi(choice) > 0 
							&& std::stoi(choice) <= player->get_inventory()->size() 
							&& (*player->get_inventory())[std::stoi(choice) - 1] != NULL)
						{
							if (HealPotion* healPotion = dynamic_cast<HealPotion *>((*player->get_inventory())[std::stoi(choice) - 1]))
							{
								std::cout << "[-] Cannot select heal potion as active item\n [-]Potions can be used only in battle\n\n";
							}
							else {
								if (player->get_active_item() != NULL)
								{
									Item *temp;
									temp = player->get_active_item();
									player->equip((*player->get_inventory())[std::stoi(choice) - 1]);
									(*player->get_inventory())[std::stoi(choice) - 1] = temp;
								}
								else {
									player->equip((*player->get_inventory())[std::stoi(choice) - 1]);
									(*player->get_inventory()).pop_back();
								}
								std::cout << "[+] Successfully selected!\n\n";
							}
						}
						else {
							std::cout << "[-] Wrong inventory index\n\n";
						}
					}
					else {
						std::cout << "[-] Inventory is empty\n\n";
					}
				}
			}
			else {
				std::cout << "[-] Player is NULL!\n\n";
			}
		}
		else if (choice == "exit" || choice == "e") {
			std::cout << "Goodbye!\n";
			return 0;
		}
	}

	return 0;
}