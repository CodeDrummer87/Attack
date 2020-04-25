#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <iostream>
#include <Windows.h>

#include "Animation.h"
#include "Entity.h"

#include "Player.h"
#include "Shell.h"

#include "Enemy.h"
#include "FirstStage.h"

using namespace std;
using namespace sf;

int main()
{
#pragma region Window Settings

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int sizeX = GetSystemMetrics(SM_CXFULLSCREEN);
	int sizeY = GetSystemMetrics(SM_CYFULLSCREEN);

	if (sizeX > 1500 && sizeX < 1920)
	{
		sizeX = 1920;
		sizeY = 1080;
	}

	RenderWindow app(VideoMode(sizeX, sizeY), "Attack", Style::Fullscreen);
	app.setFramerateLimit(60);
	app.setMouseCursorVisible(false);
	app.setKeyRepeatEnabled(false);

#pragma endregion

#pragma region Images | Textures | Sounds | Animations

#pragma region Images

	Image iBurgundyTank, iYellowTank, iPurpleTank, iLightBlueTank, iHemoTank, iEnemy_1;
	iBurgundyTank.loadFromFile("source/images/models/tanks/players/burgundyTank.png");
	iBurgundyTank.createMaskFromColor(Color::White);

	iYellowTank.loadFromFile("source/images/models/tanks/players/yellowTank.png");
	iYellowTank.createMaskFromColor(Color::White);

	iPurpleTank.loadFromFile("source/images/models/tanks/players/purpleTank.png");
	iPurpleTank.createMaskFromColor(Color::White);

	iLightBlueTank.loadFromFile("source/images/models/tanks/players/lightBlueTank.png");
	iLightBlueTank.createMaskFromColor(Color::White);

	iHemoTank.loadFromFile("source/images/models/tanks/players/hemoTank.png");
	iHemoTank.createMaskFromColor(Color::White);

	iEnemy_1.loadFromFile("source/images/models/tanks/enemies/enemy_1.png");
	iEnemy_1.createMaskFromColor(Color::White);

#pragma endregion

#pragma region Textures

	Texture bTank, yTank, pTank, lbTank, hTank, tTankRound, tShell, tShellExp, tSmoke, tEnemy_1,
		tRank, tMap;
	bTank.loadFromImage(iBurgundyTank);
	yTank.loadFromImage(iYellowTank);
	pTank.loadFromImage(iPurpleTank);
	lbTank.loadFromImage(iLightBlueTank);
	hTank.loadFromImage(iHemoTank);
	tTankRound.loadFromFile("source/images/models/tanks/round.png");
	tShell.loadFromFile("source/images/models/tanks/shell.png");
	tShellExp.loadFromFile("source/images/models/explosion/shell_explosion.png");
	tSmoke.loadFromFile("source/images/models/smoke/smoke.png");
	tEnemy_1.loadFromImage(iEnemy_1);
	tRank.loadFromFile("source/images/attributes/ranks.png");
	tMap.loadFromFile("source/images/map.png");

#pragma endregion

#pragma region Sounds

	SoundBuffer bTankBuf, yTankBuf, pTankBuf, tankExpBuf,
		burgTankRoundBuf, yelTankRoundBuf, purpTankRoundBuf,
		shellExpBuf, enemy_1Buf, en_1RoundBuf, armorBuf, prefermentBuf;

	bTankBuf.loadFromFile("source/sounds/tank/movement/move_1.ogg");
	yTankBuf.loadFromFile("source/sounds/tank/movement/move_2.ogg");
	pTankBuf.loadFromFile("source/sounds/tank/movement/move_3.ogg");
	tankExpBuf.loadFromFile("source/sounds/tank/explosion/tank_explosion.ogg");
	burgTankRoundBuf.loadFromFile("source/sounds/tank/round/burgundy_tank_round.ogg");
	purpTankRoundBuf.loadFromFile("source/sounds/tank/round/purple_tank_round.ogg");
	yelTankRoundBuf.loadFromFile("source/sounds/tank/round/yellow_tank_round.ogg");
	shellExpBuf.loadFromFile("source/sounds/explosion/shell_explosion.ogg");
	enemy_1Buf.loadFromFile("source/sounds/tank/movement/move_5.ogg");
	en_1RoundBuf.loadFromFile("source/sounds/tank/round/enemy1_round.ogg");
	armorBuf.loadFromFile("source/sounds/tank/armor.ogg");
	prefermentBuf.loadFromFile("source/sounds/effects/preferment.ogg");

	Sound enemy_1Move, sArmor, sPreferment;
	enemy_1Move.setBuffer(enemy_1Buf);		enemy_1Move.setLoop(true);
	sArmor.setBuffer(armorBuf);				sArmor.setLoop(false);
	sPreferment.setBuffer(prefermentBuf);	sPreferment.setLoop(false);		sPreferment.setVolume(32.f);

	Music chapter_finale;
	chapter_finale.openFromFile("source/sounds/music/chapter_finale.ogg");
	chapter_finale.play();

#pragma endregion

#pragma region Animations

	Animation burgundy_tank(bTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_burg_tank(bTank, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

	Animation yellow_tank(yTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_yel_tank(yTank, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

	Animation purple_tank(pTank, pTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_purp_tank(pTank, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

	Animation lightblue_tank(lbTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_lb_tank(lbTank, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

	Animation hemo_tank(hTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_hemo_tank(hTank, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

	Animation aBurgTankRound(tTankRound, burgTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aYelTankRound(tTankRound, yelTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aPurpTankRound(tTankRound, purpTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aShell(tShell, 0, 0, 64, 64, 0.01, 2);
	Animation aShellExp(tShellExp, shellExpBuf, 0, 0, 64, 64, 0.01, 7);
	Animation aSmoke(tSmoke, 0, 0, 64, 64, 0.006, 5);
	Animation aRank(tRank, 0, 0, 60, 134, 1, 18);

	Animation enemy_1(tEnemy_1, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_1(tEnemy_1, tankExpBuf, 0, 64, 64, 64, 0.009, 12);
	Animation aEnemy1Round(tTankRound, en_1RoundBuf, 0, 0, 40, 36, 0.015, 8);

	Animation map(tMap, 0, 64, 32, 32, 0.003, 8);

#pragma endregion

#pragma endregion

	Player *player_1 = new Player(burgundy_tank, explosion_burg_tank, 790, 1000, 1, 1);
	Player *player_2 = new Player(yellow_tank, explosion_yel_tank, 870, 950, 1, 1);
	Player *player_3 = new Player(purple_tank, explosion_purp_tank, 950, 900, 1, 1);
	Player *player_4 = new Player(lightblue_tank, explosion_lb_tank, 1030, 950, 1, 1);
	Player *player_5 = new Player(hemo_tank, explosion_hemo_tank, 1110, 1000, 1, 1);

	vector<Entity*> entities;
	entities.push_back(player_1);
	entities.push_back(player_2);
	entities.push_back(player_3);
	entities.push_back(player_4);
	entities.push_back(player_5);

	//.:: Enemies ::: (temporary code for testing)
	const int eTanks = 18;

	Enemy* squad[eTanks];
	int enemyPositionX = 70;
	int enemyPositionY = 100;
	for (int i = 0; i < eTanks; i++)
	{
		squad[i] = new Enemy(enemy_1, explosion_enemy_1, enemyPositionX, enemyPositionY, 3, 1);
		entities.push_back(squad[i]);
		enemyPositionX += 200;
		if (i == 9)
		{
			enemyPositionX = 100;
			enemyPositionY += 65;
		}
	}

	enemy_1Move.play();
	bool enemy_1Alive = true;
	//--------------------------------------------

	Clock clock;

	while (app.isOpen())
	{
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time /= 1700;

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			//.:: Tank rounds :::::::::::::::
			if (event.type == Event::KeyPressed)
			{
				//.:: Tank round (player 1)
				if (player_1->status != DEAD)
				{
					if (event.key.code == Keyboard::LControl)
					{
						if (player_1->isShot)
						{
							player_1->isShot = false;

							Entity *round = new Entity(aBurgTankRound, player_1, "explosion");
							Shell *shell = new Shell(aShell, aShellExp, player_1);
							entities.push_back(round);
							entities.push_back(shell);
						}
					}
				}

				//.:: Tank round (player 2)
				if (player_2->status != DEAD)
				{
					if (event.key.code == Keyboard::Space)
					{
						if (player_2->isShot)
						{
							player_2->isShot = false;

							Entity *round = new Entity(aYelTankRound, player_2, "explosion");
							Shell *shell = new Shell(aShell, aShellExp, player_2);
							entities.push_back(round);
							entities.push_back(shell);
						}
					}
				}

				//.:: Tank round (player 3)
				if (player_3->status != DEAD)
				{
					if (event.key.code == Keyboard::Enter)
					{
						if (player_3->isShot)
						{
							player_3->isShot = false;

							Entity *round = new Entity(aPurpTankRound, player_3, "explosion");
							Shell *shell = new Shell(aShell, aShellExp, player_3);
							entities.push_back(round);
							entities.push_back(shell);
						}
					}
				}

				//.:: Tank round (player 4)
				if (player_4->status != DEAD)
				{
					if (event.key.code == Keyboard::RControl)
					{
						if (player_4->isShot)
						{
							player_4->isShot = false;

							Entity *round = new Entity(aYelTankRound, player_4, "explosion");
							Shell *shell = new Shell(aShell, aShellExp, player_4);
							entities.push_back(round);
							entities.push_back(shell);
						}
					}
				}

				//.:: Tank round (player 5)
				if (player_5->status != DEAD)
				{
					if (event.key.code == Keyboard::Numpad7)
					{
						if (player_5->isShot)
						{
							player_5->isShot = false;

							Entity *round = new Entity(aBurgTankRound, player_5, "explosion");
							Shell *shell = new Shell(aShell, aShellExp, player_5);
							entities.push_back(round);
							entities.push_back(shell);
						}
					}
				}
			}
		}

#pragma region First Player control

		if (player_1->status != DEAD)
		{
			//.:: Smoking :::::::::::::::::::
			if (player_1->status == WOUNDED)
			{
				if (!player_1->isSmoking)
				{
					player_1->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_1, "smoke");
					entities.push_back(smoke);
				}
			}

			//.:: GetRank ::::::::::::::::::
			if (player_1->preferment)
			{
				player_1->preferment = false;
				sPreferment.play();
				if (!player_1->hasRank)
				{
					player_1->hasRank = true;
					Entity *rank = new Entity(aRank, player_1, "rank");
					entities.push_back(rank);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player_1->accelerate(1, -0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player_1->accelerate(2, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player_1->accelerate(3, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player_1->accelerate(4, -0.08 * time);
			}
			else player_1->playAnimation = false;
		}
		else
		{
			if (!player_1->isSmoking && player_1->makeSureDestroyed())
			{
				player_1->isSmoking = true;
				Entity *smoke = new Entity(aSmoke, player_1, "smoke");
				entities.push_back(smoke);
			}
		}

#pragma endregion

#pragma region Second Player control

		if (player_2->status != DEAD)
		{
			//.:: Smoking ::::::::::::::::::
			if (player_2->status == WOUNDED)
			{
				if (!player_2->isSmoking)
				{
					player_2->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_2, "smoke");
					entities.push_back(smoke);
				}
			}

			//.:: GetRank ::::::::::::::::::
			if (player_2->preferment)
			{
				player_2->preferment = false;
				sPreferment.play();
				if (!player_2->hasRank)
				{
					player_2->hasRank = true;
					Entity *rank = new Entity(aRank, player_2, "rank");
					entities.push_back(rank);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::T))
			{
				player_2->accelerate(1, -0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::H))
			{
				player_2->accelerate(2, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::G))
			{
				player_2->accelerate(3, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::F))
			{
				player_2->accelerate(4, -0.08 * time);
			}
			else player_2->playAnimation = false;
		}
		else
		{
			if (!player_2->isSmoking && player_2->makeSureDestroyed())
			{
				player_2->isSmoking = true;
				Entity *smoke = new Entity(aSmoke, player_2, "smoke");
				entities.push_back(smoke);
			}
		}

#pragma endregion

#pragma region Third Player control

		if (player_3->status != DEAD)
		{
			//.:: Smoking ::::::::::::::::::
			if (player_3->status == WOUNDED)
			{
				if (!player_3->isSmoking)
				{
					player_3->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_3, "smoke");
					entities.push_back(smoke);
				}
			}

			//.:: GetRank ::::::::::::::::::
			if (player_3->preferment)
			{
				player_3->preferment = false;
				sPreferment.play();
				if (!player_3->hasRank)
				{
					player_3->hasRank = true;
					Entity *rank = new Entity(aRank, player_3, "rank");
					entities.push_back(rank);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::I))
			{
				player_3->accelerate(1, -0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::L))
			{
				player_3->accelerate(2, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::K))
			{
				player_3->accelerate(3, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::J))
			{
				player_3->accelerate(4, -0.08 * time);
			}
			else player_3->playAnimation = false;
		}
		else
		{
			if (!player_3->isSmoking && player_3->makeSureDestroyed())
			{
				player_3->isSmoking = true;
				Entity *smoke = new Entity(aSmoke, player_3, "smoke");
				entities.push_back(smoke);
			}
		}

#pragma endregion

#pragma region Forth Player control

		if (player_4->status != DEAD)
		{
			//.:: Smoking ::::::::::::::::::
			if (player_4->status == WOUNDED)
			{
				if (!player_4->isSmoking)
				{
					player_4->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_4, "smoke");
					entities.push_back(smoke);
				}
			}

			//.:: GetRank ::::::::::::::::::
			if (player_4->preferment)
			{
				player_4->preferment = false;
				sPreferment.play();
				if (!player_4->hasRank)
				{
					player_4->hasRank = true;
					Entity *rank = new Entity(aRank, player_4, "rank");
					entities.push_back(rank);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				player_4->accelerate(1, -0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				player_4->accelerate(2, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				player_4->accelerate(3, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				player_4->accelerate(4, -0.08 * time);
			}
			else player_4->playAnimation = false;
		}
		else
		{
			if (!player_4->isSmoking && player_4->makeSureDestroyed())
			{
				player_4->isSmoking = true;
				Entity *smoke = new Entity(aSmoke, player_4, "smoke");
				entities.push_back(smoke);
			}
		}

#pragma endregion

#pragma region Fifth Player control

		if (player_5->status != DEAD)
		{
			//.:: Smoking ::::::::::::::::::
			if (player_5->status == WOUNDED)
			{
				if (!player_5->isSmoking)
				{
					player_5->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_5, "smoke");
					entities.push_back(smoke);
				}
			}

			//.:: GetRank ::::::::::::::::::
			if (player_5->preferment)
			{
				player_5->preferment = false;
				sPreferment.play();
				if (!player_5->hasRank)
				{
					player_5->hasRank = true;
					Entity *rank = new Entity(aRank, player_5, "rank");
					entities.push_back(rank);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Numpad8))
			{
				player_5->accelerate(1, -0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Numpad6))
			{
				player_5->accelerate(2, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Numpad5))
			{
				player_5->accelerate(3, 0.08 * time);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Numpad4))
			{
				player_5->accelerate(4, -0.08 * time);
			}
			else player_5->playAnimation = false;
		}
		else
		{
			if (!player_5->isSmoking && player_5->makeSureDestroyed())
			{
				player_5->isSmoking = true;
				Entity *smoke = new Entity(aSmoke, player_5, "smoke");
				entities.push_back(smoke);
			}
		}

#pragma endregion

		//.:: Temporary code for testing :::
		enemy_1Alive = false;
		for (int i = 0; i < eTanks; i++)
			if (squad[i]->status != DEAD)
			{
				if(squad[i]->round)
					if (squad[i]->isShot)
					{
						squad[i]->round = false;
						squad[i]->isShot = false;
						Entity *round = new Entity(aEnemy1Round, squad[i], "explosion");
						Shell *shell = new Shell(aShell, aShellExp, squad[i]);
						entities.push_back(round);
						entities.push_back(shell);
					}

				enemy_1Alive = true;
				if (squad[i]->status == WOUNDED)
				{
					if (!squad[i]->isSmoking)
					{
						squad[i]->isSmoking = true;
						Entity *smoke = new Entity(aSmoke, squad[i], "smoke");
						entities.push_back(smoke);
					}
				}
			}
			else
			{
				if (!squad[i]->isSmoking && squad[i]->makeSureDestroyed())
				{
					squad[i]->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, squad[i], "smoke");
					entities.push_back(smoke);
				}
			}
		//----------------------------------
		if (!enemy_1Alive)
		{
			enemy_1Move.stop();
			app.close();
		}

		//.:: collision :::
		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "tank" || a->name == "shell")
					a->getCollision(FirstStage);
				if (a->tokenId != b->tokenId)
				{
					if (a->name == "tank" && b->name == "tank" || b->name == "destroyed")
						a->collideEntities(b);
					if (a->name != "smoke" && a->name != "explosion" && a->name != "rank"
						&& b->name != "smoke" && b->name != "explosion" && b->name != "rank")
						if (a->name == "shell" && b->name == "tank")
							a->damageEntity(b, sArmor);
				}
			}

		//.:: update entities :::
		for (auto i  = entities.begin(); i != entities.end();)
		{
			Entity* e = *i;
			e->update(time);
			e->anim.update(time, e->playAnimation, e->dir);

			if (e->isExist == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		app.clear();
		drawMap(FirstStage, app, map, time);
		//.:: display entities :::
		for (auto e : entities)
			e->draw(app);
		drawForest(FirstStage, app, map);
		app.display();
	}

	return 0;
}