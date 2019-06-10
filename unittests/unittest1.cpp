#include "stdafx.h"
#include "CppUnitTest.h"

#include "game.h"
#include "player.h"
#include "enemy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::string pName = "AAAAAAAA";
			int pHealth = 20;
			int pDmg = 2;
			Player *player = new Player(pName, pHealth, pDmg);
			
			std::string eName = "BBBBBBBB";
			int eHealth = 10;
			int eDmg = 1;
			Enemy *enemy= new Enemy(eName, eHealth, eDmg);

			Assert::AreEqual(eHealth - pDmg, player->attack(enemy));
		}

		TEST_METHOD(TestMethod2)
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
	};
}