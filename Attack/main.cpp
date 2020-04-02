#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <iostream>
#include <Windows.h>

#include "Animation.h"
#include "Entity.h"

#include "Tank.h"
#include "Shell.h"

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

	Image iBurgundyTank, iYellowTank, iPurpleTank, iLightBlueTank, iHemoTank;
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

#pragma endregion

#pragma region Textures

	Texture bTank, yTank, pTank, lbTank, hTank, tTankRound, tShell, tShellExp, tSmoke;
	bTank.loadFromImage(iBurgundyTank);
	yTank.loadFromImage(iYellowTank);
	pTank.loadFromImage(iPurpleTank);
	lbTank.loadFromImage(iLightBlueTank);
	hTank.loadFromImage(iHemoTank);
	tTankRound.loadFromFile("source/images/models/tanks/round.png");
	tShell.loadFromFile("source/images/models/tanks/shell.png");
	tShellExp.loadFromFile("source/images/models/explosion/shell_explosion.png");
	tSmoke.loadFromFile("source/images/models/smoke/smoke.png");

#pragma endregion

#pragma region Sounds

	SoundBuffer bTankBuf, yTankBuf, pTankBuf, tankExpBuf, burgTankRoundBuf, yelTankRoundBuf, purpTankRoundBuf, shellExpBuf;
	bTankBuf.loadFromFile("source/sounds/tank/movement/move_1.ogg");
	yTankBuf.loadFromFile("source/sounds/tank/movement/move_2.ogg");
	pTankBuf.loadFromFile("source/sounds/tank/movement/move_3.ogg");
	tankExpBuf.loadFromFile("source/sounds/tank/explosion/tank_explosion.ogg");
	burgTankRoundBuf.loadFromFile("source/sounds/tank/round/burgundy_tank_round.ogg");
	purpTankRoundBuf.loadFromFile("source/sounds/tank/round/purple_tank_round.ogg");
	yelTankRoundBuf.loadFromFile("source/sounds/tank/round/yellow_tank_round.ogg");
	shellExpBuf.loadFromFile("source/sounds/explosion/shell_explosion.ogg");

#pragma endregion

#pragma region Animations

	Animation burgundy_tank(bTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_burg_tank(bTank, tankExpBuf, 0, 64, 64, 64, 0.008, 12);

	Animation yellow_tank(yTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_yel_tank(yTank, tankExpBuf, 0, 64, 64, 64, 0.008, 12);

	Animation purple_tank(pTank, pTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_purp_tank(pTank, tankExpBuf, 0, 64, 64, 64, 0.008, 12);

	Animation lightblue_tank(lbTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_lb_tank(lbTank, tankExpBuf, 0, 64, 64, 64, 0.008, 12);

	Animation hemo_tank(hTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_hemo_tank(hTank, tankExpBuf, 0, 64, 64, 64, 0.008, 12);

	Animation aBurgTankRound(tTankRound, burgTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aYelTankRound(tTankRound, yelTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aPurpTankRound(tTankRound, purpTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aShell(tShell, 0, 0, 64, 64, 0.01, 2);
	Animation aShellExp(tShellExp, shellExpBuf, 0, 0, 64, 64, 0.01, 7);
	Animation aSmoke(tSmoke, 0, 0, 64, 64, 0.006, 5);

#pragma endregion

#pragma endregion

	Tank *player_1 = new Tank(burgundy_tank, explosion_burg_tank, 550, 800, 1, "player");
	Tank *player_2 = new Tank(yellow_tank, explosion_yel_tank, 750, 800, 1, "player");
	Tank *player_3 = new Tank(purple_tank, explosion_purp_tank, 950, 800, 1, "player");
	Tank *player_4 = new Tank(lightblue_tank, explosion_lb_tank, 1150, 800, 1, "player");
	Tank *player_5 = new Tank(hemo_tank, explosion_hemo_tank, 1350, 800, 1, "player");

	vector<Entity*> entities;
	entities.push_back(player_1);
	entities.push_back(player_2);
	entities.push_back(player_3);
	entities.push_back(player_4);
	entities.push_back(player_5);

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
						Entity *round = new Entity(aBurgTankRound, player_1->getCoordX(true), player_1->getCoordY(true), player_1->dir);
						Shell *shell = new Shell(aShell, aShellExp, player_1->getCoordX(true), player_1->getCoordY(true), player_1->dir);
						entities.push_back(round);
						entities.push_back(shell);
					}
				}

				//.:: Tank round (player 2)
				if (player_2->status != DEAD)
				{
					if (event.key.code == Keyboard::Space)
					{
						Entity *round = new Entity(aYelTankRound, player_2->getCoordX(true), player_2->getCoordY(true), player_2->dir);
						Shell *shell = new Shell(aShell, aShellExp, player_2->getCoordX(true), player_2->getCoordY(true), player_2->dir);
						entities.push_back(round);
						entities.push_back(shell);
					}
				}

				//.:: Tank round (player 3)
				if (player_3->status != DEAD)
				{
					if (event.key.code == Keyboard::Enter)
					{
						Entity *round = new Entity(aPurpTankRound, player_3->getCoordX(true), player_3->getCoordY(true), player_3->dir);
						Shell *shell = new Shell(aShell, aShellExp, player_3->getCoordX(true), player_3->getCoordY(true), player_3->dir);
						entities.push_back(round);
						entities.push_back(shell);
					}
				}

				//.:: Tank round (player 4)
				if (player_4->status != DEAD)
				{
					if (event.key.code == Keyboard::RControl)
					{
						Entity *round = new Entity(aYelTankRound, player_4->getCoordX(true), player_4->getCoordY(true), player_4->dir);
						Shell *shell = new Shell(aShell, aShellExp, player_4->getCoordX(true), player_4->getCoordY(true), player_4->dir);
						entities.push_back(round);
						entities.push_back(shell);
					}
				}

				//.:: Tank round (player 5)
				if (player_5->status != DEAD)
				{
					if (event.key.code == Keyboard::Numpad7)
					{
						Entity *round = new Entity(aBurgTankRound, player_5->getCoordX(true), player_5->getCoordY(true), player_5->dir);
						Shell *shell = new Shell(aShell, aShellExp, player_5->getCoordX(true), player_5->getCoordY(true), player_5->dir);
						entities.push_back(round);
						entities.push_back(shell);
					}
				}
			}
		}

#pragma region First Player control

		if (player_1->status != DEAD)
		{
			if (player_1->status == WOUNDED)
			{
				if (!player_1->isSmoking)
				{
					player_1->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_1->getCoordX(false), player_1->getCoordY(false));
					entities.push_back(smoke);
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

#pragma endregion

#pragma region Second Player control

		if (player_2->status != DEAD)
		{
			if (player_2->status == WOUNDED)
			{
				if (!player_2->isSmoking)
				{
					player_2->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_2->getCoordX(false), player_2->getCoordY(false));
					entities.push_back(smoke);
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

#pragma endregion

#pragma region Third Player control

		if (player_3->status != DEAD)
		{
			if (player_3->status == WOUNDED)
			{
				if (!player_3->isSmoking)
				{
					player_3->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_3->getCoordX(false), player_3->getCoordY(false));
					entities.push_back(smoke);
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

#pragma endregion

#pragma region Forth Player control

		if (player_4->status != DEAD)
		{
			if (player_4->status == WOUNDED)
			{
				if (!player_4->isSmoking)
				{
					player_4->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_4->getCoordX(false), player_4->getCoordY(false));
					entities.push_back(smoke);
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

#pragma endregion

#pragma region Fifth Player control

		if (player_5->status != DEAD)
		{
			if (player_5->status == WOUNDED)
			{
				if (!player_5->isSmoking)
				{
					player_5->isSmoking = true;
					Entity *smoke = new Entity(aSmoke, player_5->getCoordX(false), player_5->getCoordY(false));
					entities.push_back(smoke);
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

#pragma endregion

		//.:: collision :::
		for (auto a : entities)
			for (auto b : entities)
				if(a->tokenId != b->tokenId)
					if(a->name == "player" && b->name == "player")
						a->collideEntities(b);

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
		//.:: display entities :::
		for (auto e : entities)
			e->draw(app);
		app.display();
	}

	return 0;
}