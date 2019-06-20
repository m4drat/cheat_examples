#include "stdafx.h"
#include "CppUnitTest.h"

#include "game.h"
#include "player.h"
#include "enemy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(TestPlayerClass)
	{
	public:

		TEST_METHOD(TestIncreaseGold)
		{
			std::string pName = "madrat";
			Player *player = new Player(pName);

			int gold = 20;
			player->increase_gold(gold);

			Assert::AreEqual(player->get_gold(), gold);
		}

		TEST_METHOD(TestDecreaseGold)
		{
			std::string pName = "madrat";
			Player *player = new Player(pName);

			int inc_gold = 40;
			player->increase_gold(inc_gold);
			
			int dec_gold = 30;
			player->decrease_gold(dec_gold);

			Assert::AreEqual(player->get_gold(), inc_gold - dec_gold);
		}

		TEST_METHOD(TestIncreaseExp)
		{
			std::string pName = "madrat";
			Player *player = new Player(pName);

			int exp = 20;
			player->increase_exp(exp);

			Assert::AreEqual(player->get_exp(), exp);
		}

		TEST_METHOD(TestDecreaseExp)
		{
			std::string pName = "madrat";
			Player *player = new Player(pName);

			int inc_exp = 40;
			player->increase_exp(inc_exp);

			int dec_exp = 30;
			player->decrease_exp(dec_exp);

			Assert::AreEqual(player->get_exp(), inc_exp - dec_exp);
		}

		TEST_METHOD(TestIncreaseTotalKilled)
		{
			std::string pName = "madrat";
			Player *player = new Player(pName);

			player->increase_total_killed();
			player->increase_total_killed();
			player->increase_total_killed();

			Assert::AreEqual(player->get_total_killed(), 3);
		}

		TEST_METHOD(TestDecreaseHealth)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pDmg);

			int damage = 20;
			player->decrease_health(damage);

			Assert::AreEqual(player->get_health(), pHealth - damage);
		}

		TEST_METHOD(TestIncreaseHealth)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			int inc_hp = 20;
			player->increase_health(inc_hp);

			Assert::AreEqual(player->get_health(), pHealth + inc_hp);
		}

		TEST_METHOD(TestAttackEnemy)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			std::string eName = "goblin";
			int eHealth = 135;
			int eDmg = 51;
			Enemy *enemy = new Enemy(eName, eHealth, eDmg);

			player->attack(enemy);

			Assert::AreEqual(enemy->get_health(), eHealth - pDmg);
		}

		TEST_METHOD(TestAttackEnemySpecDamageVal)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			std::string eName = "goblin";
			int eHealth = 135;
			int eDmg = 51;
			Enemy *enemy = new Enemy(eName, eHealth, eDmg);

			int playerAttackPower = 21;
			player->attack(enemy, playerAttackPower);

			Assert::AreEqual(enemy->get_health(), eHealth - playerAttackPower);
		}

		TEST_METHOD(TestHealYourself)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 12, 20, pDmg * 2, 1, pDmg);

			player->heal(player);

			Assert::AreEqual(player->get_health(), pHealth + player->get_heal());
		}

		TEST_METHOD(TestHealYourselfSpecVal)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			int healAmount = 19;
			player->heal(player, healAmount);

			Assert::AreEqual(player->get_health(), healAmount + pHealth);
		}

		TEST_METHOD(TestLiftItem)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			Sword *sword = new Sword();
			player->lift_item(sword);

			Assert::AreEqual(player->get_inventory()->size(), size_t(1));
		}

		TEST_METHOD(TestEquipItem)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			Sword *sword = new Sword();
			player->equip(sword);

			Assert::IsNotNull(player->get_active_item());
		}

		TEST_METHOD(TestDie)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			player->die();

			Assert::AreEqual(player->get_isAlive(), false);
		}
	};
}