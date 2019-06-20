#include "stdafx.h"
#include "CppUnitTest.h"

#include "game.h"
#include "player.h"
#include "enemy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(TestGameLogic)
	{
	public:

		TEST_METHOD(TestAttack)
		{
			std::string pName = "AAAAAAAA";
			int pHealth = 20;
			int pDmg = 2;
			Player *player = new Player(pName, pHealth, pDmg);

			std::string eName = "BBBBBBBB";
			int eHealth = 10;
			int eDmg = 1;
			Enemy *enemy = new Enemy(eName, eHealth, eDmg);

			Assert::AreEqual(eHealth - pDmg, player->attack(enemy));
		}

		TEST_METHOD(TestAttackUnderZero)
		{
			std::string pName = "madrat";
			int pHealth = 2023;
			int pDmg = 18;
			Player *player = new Player(pName, pHealth, pDmg);

			std::string eName = "goblin";
			int eHealth = 9;
			int eDmg = 5;
			Enemy *enemy = new Enemy(eName, eHealth, eDmg);

			Assert::AreEqual(0, player->attack(enemy));
		}

		TEST_METHOD(TestPlayerEquip)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pDmg);

			Bow *bow = new Bow();

			player->equip(bow);

			Item *equipedItem = player->get_active_item();

			Assert::IsNotNull(equipedItem);
		}

		TEST_METHOD(TestHealUsingPotion)
		{
			std::string pName = "madrat";
			int pHealth = 240;
			int pDmg = 64;
			Player *player = new Player(pName, pHealth, pHealth * 2, 0, 0, 0, pDmg * 2, 1, pDmg);

			HealPotion* healPotion = new HealPotion();

			healPotion->use(player);

			Assert::AreEqual(pHealth + healPotion->get_heal_val(), player->get_health());
		}
	};
}