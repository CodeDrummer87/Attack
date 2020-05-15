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

#include "View.h"
#include "Foreground.h"

using namespace std;
using namespace sf;

int main()
{
#pragma region Window Settings

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int sizeX = GetSystemMetrics(SM_CXSCREEN);
	int sizeY = GetSystemMetrics(SM_CYSCREEN);

	if (sizeX != 1280 && sizeY != 1024)
	{
		sizeX = 1920;
		sizeY = 1080;
	}

	view.reset(FloatRect(0, 0, sizeX, sizeY));

	SoundBuffer startBuf;
	startBuf.loadFromFile("source/sounds/foreground/start.ogg");

	Sound start(startBuf);

	Music *foregroundTheme = new Music();
	foregroundTheme->openFromFile("source/sounds/foreground/main_theme.ogg");
	foregroundTheme->setVolume(70.f);
	foregroundTheme->play();

	bool game = true;
	int numberOfPlayers = 1;
	showForeground(sizeX, sizeY, game, numberOfPlayers, start);

	if (game)
	{
		RenderWindow app(VideoMode(sizeX, sizeY), "Attack", Style::Fullscreen);
		app.setFramerateLimit(60);
		app.setMouseCursorVisible(false);
		app.setKeyRepeatEnabled(false);

		view.setCenter(W * 32 / 2 - 16, H * 32 - sizeY / 2 - 32);

#pragma endregion

#pragma region Images | Textures | Sounds | Animations

#pragma region Images

		Image iBurgundyTank, iYellowTank, iPurpleTank, iLightBlueTank, iHemoTank, iEnemy_1, iEnemy_2, iEnemy_3, iEnemy_4, iMap, iIcon, iDrowning;
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

		iEnemy_2.loadFromFile("source/images/models/tanks/enemies/enemy_2.png");
		iEnemy_2.createMaskFromColor(Color::White);

		iEnemy_3.loadFromFile("source/images/models/tanks/enemies/enemy_3.png");
		iEnemy_3.createMaskFromColor(Color::White);

		iEnemy_4.loadFromFile("source/images/models/tanks/enemies/enemy_4.png");
		iEnemy_4.createMaskFromColor(Color::White);

		iMap.loadFromFile("source/images/map.png");
		iMap.createMaskFromColor(Color::White);

		iIcon.loadFromFile("source/images/icons.png");
		iIcon.createMaskFromColor(Color::White);

		iDrowning.loadFromFile("source/images/models/other/drowning.png");
		iDrowning.createMaskFromColor(Color::White);

#pragma endregion

#pragma region Textures

		Texture bTank, yTank, pTank, lbTank, hTank, tTankRound, tShell, tShellExp, tSmoke,
			tEnemy_1, tEnemy_2, tEnemy_3, tEnemy_4, tRank, tMap, tIcon, tDrowning;
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
		tEnemy_2.loadFromImage(iEnemy_2);
		tEnemy_3.loadFromImage(iEnemy_3);
		tEnemy_4.loadFromImage(iEnemy_4);
		tRank.loadFromFile("source/images/attributes/ranks.png");
		tMap.loadFromImage(iMap);
		tIcon.loadFromImage(iIcon);
		tDrowning.loadFromImage(iDrowning);

#pragma endregion

#pragma region Sounds

		SoundBuffer bTankBuf, yTankBuf, pTankBuf, tankExpBuf,
			burgTankRoundBuf, yelTankRoundBuf, purpTankRoundBuf,
			shellExpBuf, enemy_1Buf, en_1RoundBuf, armorBuf, prefermentBuf,
			takingIconBuf, drowningBuf, laughBuf;

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
		takingIconBuf.loadFromFile("source/sounds/icons/take_icon.ogg");
		drowningBuf.loadFromFile("source/sounds/effects/drowning.ogg");
		laughBuf.loadFromFile("source/sounds/effects/laugh.ogg");

		Sound enemy_move, sArmor, sPreferment, sTakingIcon, sLaugh(laughBuf);
		enemy_move.setBuffer(enemy_1Buf);		enemy_move.setLoop(true);
		sArmor.setBuffer(armorBuf);				sArmor.setLoop(false);
		sPreferment.setBuffer(prefermentBuf);	sPreferment.setLoop(false);		sPreferment.setVolume(32.f);
		sTakingIcon.setBuffer(takingIconBuf);	sTakingIcon.setLoop(false);

		Music chapter_finale;
		chapter_finale.openFromFile("source/sounds/music/chapter_finale.ogg");
		//chapter_finale.play();

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

		Animation enemy_2(tEnemy_2, 0, 0, 64, 64, 0.016, 2);
		Animation explosion_enemy_2(tEnemy_2, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

		Animation enemy_3(tEnemy_3, 0, 0, 64, 64, 0.016, 2);
		Animation explosion_enemy_3(tEnemy_3, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

		Animation enemy_4(tEnemy_4, 0, 0, 64, 64, 0.016, 2);
		Animation explosion_enemy_4(tEnemy_4, tankExpBuf, 0, 64, 64, 64, 0.009, 12);

		Animation map(tMap, 0, 64, 32, 32, 0.003, 4);
		Animation iconRepair(tIcon, 0, 0, 32, 32, 0.01, 22);
		Animation iconPreferment(tIcon, 0, 32, 32, 32, 0.02, 22);
		Animation iconCamera(tIcon, 0, 64, 32, 32, 0.02, 22);

		Animation icons[] = { iconRepair, iconPreferment, iconCamera };

		Animation aDrowning(tDrowning, drowningBuf, 0, 0, 64, 64, 0.02, 14);

#pragma endregion

#pragma endregion

		vector<Entity*> entities;
		vector<Player*> team;

		int a1, a2, b1, b2, c1, c2, d1, d2, e1, e2;
		a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = 0;

		switch (numberOfPlayers)
		{
		case 1: a1 = 950; a2 = 2050; break;
		case 2: a1 = 870; a2 = 2050; b1 = 1030; b2 = 2050; break;
		case 3: a1 = 870; a2 = 2050; b1 = 950; b2 = 2000; c1 = 1030; c2 = 2050; break;
		case 4: a1 = 810; a2 = 2050; b1 = 890; b2 = 2000;
			c1 = 1010; c2 = 2000; d1 = 1090; d2 = 2050; break;
		case 5: a1 = 790; a2 = 2100; b1 = 870; b2 = 2050; c1 = 950; c2 = 2000; 
			d1 = 1030; d2 = 2050; e1 = 1110; e2 = 2100; break;
		}

		for (int i = 0; i < numberOfPlayers; i++)
		{
			Player *player;
			switch (i)
			{
			case 0: player = new Player(burgundy_tank, explosion_burg_tank, a1, a2, 1, 1); break;
			case 1: player = new Player(yellow_tank, explosion_yel_tank, b1, b2, 1, 1); break;
			case 2: player = new Player(purple_tank, explosion_purp_tank, c1, c2, 1, 1); break;
			case 3: player = new Player(lightblue_tank, explosion_lb_tank, d1, d2, 1, 1); break;
			case 4: player = new Player(hemo_tank, explosion_hemo_tank, e1, e2, 1, 1); break;
			}

			team.push_back(player);
			entities.push_back(player);
		}

		//.:: Enemies ::: 
		const int eTanks = 36;

		vector<Enemy*> squad;
		int enemyPositionX = 70;
		int enemyPositionY = 100;
		for (int i = 0; i < eTanks; i++)
		{
			Enemy *enemy;
			if (i <= 9)
				enemy = new Enemy(enemy_4, explosion_enemy_4, enemyPositionX, enemyPositionY, 3, 4);
			else if (i > 9 && i <= 18)
				enemy = new Enemy(enemy_3, explosion_enemy_3, enemyPositionX, enemyPositionY, 3, 3);
			else if (i > 18 && i <= 27)
				enemy = new Enemy(enemy_2, explosion_enemy_2, enemyPositionX, enemyPositionY, 3, 2);
			else
				enemy = new Enemy(enemy_1, explosion_enemy_1, enemyPositionX, enemyPositionY, 3, 1);

			entities.push_back(enemy);
			squad.push_back(enemy);

			enemyPositionX += 200;
			if (i == 9 || i == 18 || i == 27)
			{
				enemyPositionX = 100;
				enemyPositionY += 400;
			}
		}

		enemy_move.play();
		bool enemy_alive = true;
		//--------------------------------------------

		Clock clock;
		Clock gameTimeClock;

		int gameTime = 0;

		//.:: Stop main theme music :::
		foregroundTheme->stop();
		delete foregroundTheme;
		//:::::::::::::::::::::::::::::

		float villainViewX = (float)sizeX / 2, villainViewY = (float)sizeY / 2;

		while (app.isOpen())
		{
			double time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time /= 1700;

			gameTime = gameTimeClock.getElapsedTime().asSeconds();
			
			Event event;
			while (app.pollEvent(event))
			{
				//.:: Tank rounds :::::::::::::::
				if (event.type == Event::KeyPressed)
				{
					//.:: Tank round (player 1)
					if (team[0]->status != DEAD)
					{
						if (event.key.code == Keyboard::LControl)
						{
							if (team[0]->isShot)
							{
								team[0]->isShot = false;

								Entity *round = new Entity(aBurgTankRound, team[0], "explosion");
								Shell *shell = new Shell(aShell, aShellExp, team[0]);
								entities.push_back(round);
								entities.push_back(shell);
							}
						}
					}

					//.:: Tank round (player 2)
					if (numberOfPlayers >= 2)
					{
						if (team[1]->status != DEAD)
						{
							if (event.key.code == Keyboard::Space)
							{
								if (team[1]->isShot)
								{
									team[1]->isShot = false;

									Entity *round = new Entity(aYelTankRound, team[1], "explosion");
									Shell *shell = new Shell(aShell, aShellExp, team[1]);
									entities.push_back(round);
									entities.push_back(shell);
								}
							}
						}
					}

					//.:: Tank round (player 3)
					if (numberOfPlayers >= 3)
					{
						if (team[2]->status != DEAD)
						{
							if (event.key.code == Keyboard::Enter)
							{
								if (team[2]->isShot)
								{
									team[2]->isShot = false;

									Entity *round = new Entity(aPurpTankRound, team[2], "explosion");
									Shell *shell = new Shell(aShell, aShellExp, team[2]);
									entities.push_back(round);
									entities.push_back(shell);
								}
							}
						}
					}

					//.:: Tank round (player 4)
					if (numberOfPlayers >= 4)
					{
						if (team[3]->status != DEAD)
						{
							if (event.key.code == Keyboard::RControl)
							{
								if (team[3]->isShot)
								{
									team[3]->isShot = false;

									Entity *round = new Entity(aYelTankRound, team[3], "explosion");
									Shell *shell = new Shell(aShell, aShellExp, team[3]);
									entities.push_back(round);
									entities.push_back(shell);
								}
							}
						}
					}

					//.:: Tank round (player 5)
					if (numberOfPlayers == 5)
					{
						if (team[4]->status != DEAD)
						{
							if (event.key.code == Keyboard::Numpad7)
							{
								if (team[4]->isShot)
								{
									team[4]->isShot = false;

									Entity *round = new Entity(aBurgTankRound, team[4], "explosion");
									Shell *shell = new Shell(aShell, aShellExp, team[4]);
									entities.push_back(round);
									entities.push_back(shell);
								}
							}
						}
					}
				}
			}

			//.:: Temporary code :::
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				app.close();

			for (auto p : team)
			{
				if (p->status != DEAD)
				{
					//.:: Smoking :::::::::::::::
					if (p->status == WOUNDED)
					{
						if (!p->isSmoking)
						{
							p->isSmoking = true;
							Entity * smoke = new Entity(aSmoke, p, "smoke");
							entities.push_back(smoke);
						}
					}

					//.:: GetRank :::::::::::::::
					if (p->preferment)
					{
						p->preferment = false;
						sPreferment.play();
						if (!p->hasRank)
						{
							p->hasRank = true;
							Entity *rank = new Entity(aRank, p, "rank");
							entities.push_back(rank);
						}
					}

					//.:: Set View :::
					if (p->isCommander && !p->cameraIsNotFree)
						setViewCoordinates(sizeX, sizeY, p->getCoordX(false), p->getCoordY(false));
				}
				else
				{
					if (p->isDrowned && !p->drowning)
					{
						p->drowning = true;
						Entity* drowning = new Entity(aDrowning, p, "drowning");
						entities.push_back(drowning);
					}

					if (p->isCommander)
					{
						p->isCommander = false;
						defineNewCommander(team);
					}

					if (!p->isSmoking && p->makeSureDestroyed())
					{
						p->isSmoking = true;
						Entity *smoke = new Entity(aSmoke, p, "smoke");
						entities.push_back(smoke);
					}
				}
			}

#pragma region First Player control

			if (team[0]->status != DEAD)
			{
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					team[0]->accelerate(1, -0.09 * time);
				}
				else if (Keyboard::isKeyPressed(Keyboard::D))
				{
					team[0]->accelerate(2, 0.09 * time);
				}
				else if (Keyboard::isKeyPressed(Keyboard::S))
				{
					team[0]->accelerate(3, 0.09 * time);
				}
				else if (Keyboard::isKeyPressed(Keyboard::A))
				{
					team[0]->accelerate(4, -0.09 * time);
				}
				else team[0]->playAnimation = false;
			}

#pragma endregion

#pragma region Second Player control

			if (numberOfPlayers >= 2)
			{
				if (team[1]->status != DEAD)
				{
					if (Keyboard::isKeyPressed(Keyboard::T))
					{
						team[1]->accelerate(1, -0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::H))
					{
						team[1]->accelerate(2, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::G))
					{
						team[1]->accelerate(3, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::F))
					{
						team[1]->accelerate(4, -0.09 * time);
					}
					else team[1]->playAnimation = false;
				}
			}

#pragma endregion

#pragma region Third Player control

			if (numberOfPlayers >= 3)
			{
				if (team[2]->status != DEAD)
				{
					if (Keyboard::isKeyPressed(Keyboard::I))
					{
						team[2]->accelerate(1, -0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::L))
					{
						team[2]->accelerate(2, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::K))
					{
						team[2]->accelerate(3, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::J))
					{
						team[2]->accelerate(4, -0.09 * time);
					}
					else team[2]->playAnimation = false;
				}
			}

#pragma endregion

#pragma region Forth Player control

			if (numberOfPlayers >= 4)
			{
				if (team[3]->status != DEAD)
				{
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						team[3]->accelerate(1, -0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						team[3]->accelerate(2, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						team[3]->accelerate(3, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						team[3]->accelerate(4, -0.09 * time);
					}
					else team[3]->playAnimation = false;
				}
			}

#pragma endregion

#pragma region Fifth Player control

			if (numberOfPlayers == 5)
			{
				if (team[4]->status != DEAD)
				{
					if (Keyboard::isKeyPressed(Keyboard::Numpad8))
					{
						team[4]->accelerate(1, -0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Numpad6))
					{
						team[4]->accelerate(2, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Numpad5))
					{
						team[4]->accelerate(3, 0.09 * time);
					}
					else if (Keyboard::isKeyPressed(Keyboard::Numpad4))
					{
						team[4]->accelerate(4, -0.09 * time);
					}
					else team[4]->playAnimation = false;
				}
			}

#pragma endregion

			enemy_alive = false;
			//.:: Enemy action
			for (auto e : squad)
			{
				if (e->status != DEAD)
				{
					if (e->round)
						if (e->isShot)
						{
							e->round = false;
							e->isShot = false;
							Entity *round = new Entity(aEnemy1Round, e, "explosion");
							Shell *shell = new Shell(aShell, aShellExp, e);
							entities.push_back(round);
							entities.push_back(shell);
						}

					enemy_alive = true;
					if (e->status == WOUNDED)
					{
						if (!e->isSmoking)
						{
							e->isSmoking = true;
							Entity *smoke = new Entity(aSmoke, e, "smoke");
							entities.push_back(smoke);
						}
					}

					if (e->isVillain)
					{
						if (e->finishVillainTime == 0)
						{
							sLaugh.play();
							view.reset(FloatRect(0, 0, villainViewX, villainViewY));
							e->finishVillainTime = gameTime + 5;
						}

						villainViewX -= villainViewX / 1000;
						villainViewY -= villainViewY / 1000;

						view.reset(FloatRect(0, 0, villainViewX, villainViewY));
						setViewCoordinates(villainViewX, villainViewY, e->getCoordX(false), e->getCoordY(false));

						if (gameTime >= e->finishVillainTime)
						{
							e->isVillain = e->cameraIsNotFree = false;
							view.reset(FloatRect(0, 0, (float)sizeX, (float)sizeY));
							e->finishVillainTime = 0;
							if (!checkTeamForCommander(team))
								view.setCenter(W * 32 / 2 - 16, H * 32 - sizeY / 2 - 32);

							villainViewX = (float)sizeX / 2;
							villainViewY = (float)sizeY / 2;
						}
					}
				}
				else
				{
					if (e->isDrowned && !e->drowning)
					{
						e->drowning = true;
						Entity* drowning = new Entity(aDrowning, e, "drowning");
						entities.push_back(drowning);
					}

					if (!e->isSmoking && e->makeSureDestroyed())
					{
						e->isSmoking = true;
						Entity *smoke = new Entity(aSmoke, e, "smoke");
						entities.push_back(smoke);
					}
				}
			}
			//----------------------------------
			if (!enemy_alive)
			{
				enemy_move.stop();
				app.close();
			}

			//.:: collision :::
			for (auto a : entities)
				for (auto b : entities)
				{
					if (a->name == "tank" || a->name == "shell" || a->name == "destroyed")
						a->getCollision(FirstStage, sTakingIcon);
					if (a->tokenId != b->tokenId)
					{
						if (a->name == "tank" && b->name == "tank" || b->name == "destroyed")
							a->collideEntities(b);
						if (a->name != "smoke" && a->name != "explosion" && a->name != "rank" && a->name != "drowning"
							&& b->name != "smoke" && b->name != "explosion" && b->name != "rank" && b->name != "drowning")
							if (a->name == "shell" && b->name == "tank")
								a->damageEntity(b, sArmor);
					}
				}

			//.:: Clearing the list of enemies
			for (auto j = squad.begin(); j != squad.end();)
			{
				Entity *enemy = *j;
				if (static_cast<Enemy*>(enemy)->drowning)
				{
					j = squad.erase(j);
				}
				else j++;
			}

			//.:: update entities :::
			for (auto i = entities.begin(); i != entities.end();)
			{
				Entity* e = *i;
				e->update(time);
				e->anim.update(time, e->playAnimation, e->dir);

				if (e->isExist == false)
				{
					i = entities.erase(i);
					delete e;
				}
				else i++;
			}

			app.setView(view);
			app.clear();
			drawMap(FirstStage, app, map, time);
			//.:: display entities :::
			for (auto e : entities)
				e->draw(app);
			drawForestAndIcons(FirstStage, app, map, icons, time);
			app.display();
		}
	}

	return 0;
}