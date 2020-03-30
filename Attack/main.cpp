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

	RenderWindow app(VideoMode(sizeX, sizeY), "Test", Style::Fullscreen);
	app.setFramerateLimit(60);
	app.setMouseCursorVisible(false);
	app.setKeyRepeatEnabled(false);

#pragma endregion

#pragma region Images | Textures | Animations | Sounds

	Image iBurgundyTank, iYellowTank;
	iBurgundyTank.loadFromFile("source/images/models/tanks/players/burgundyTank.png");
	iBurgundyTank.createMaskFromColor(Color::White);

	iYellowTank.loadFromFile("source/images/models/tanks/players/yellowTank.png");
	iYellowTank.createMaskFromColor(Color::White);

	Texture bTank, yTank, tShell, tShellExp;
	bTank.loadFromImage(iBurgundyTank);
	yTank.loadFromImage(iYellowTank);
	tShell.loadFromFile("source/images/models/tanks/shell.png");
	tShellExp.loadFromFile("source/images/models/explosion/shell_explosion.png");

	SoundBuffer bTankBuf, yTankBuf, shellExpBuf;
	bTankBuf.loadFromFile("source/sounds/tank/movement/move_1.ogg");
	yTankBuf.loadFromFile("source/sounds/tank/movement/move_2.ogg");
	shellExpBuf.loadFromFile("source/sounds/explosion/shell_explosion.ogg");

	Animation burgundy_tank(bTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation yellow_tank(yTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation aShell(tShell, 28, 27, 8, 8, 0.01, 2);
	Animation aShellExp(tShellExp, shellExpBuf, 0, 0, 64, 64, 0.01, 7);

#pragma endregion

	Tank *player_1 = new Tank();
	player_1->setEntity(burgundy_tank, 960, 800);

	Tank *player_2= new Tank();
	player_2->setEntity(yellow_tank, 960, 900);

	vector<Entity*> entities;
	entities.push_back(player_1);
	entities.push_back(player_2);

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
				if (event.key.code == Keyboard::LControl)
				{
					Shell *shell = new Shell(aShell, player_1->getCoordX(true), player_1->getCoordY(true), player_1->dir);
					entities.push_back(shell);
				}

				//.:: Tank round (player 2)
				if (event.key.code == Keyboard::Space)
				{
					Shell *shell = new Shell(aShell, player_2->getCoordX(true), player_2->getCoordY(true), player_2->dir);
					entities.push_back(shell);
				}
			}
		}

#pragma region First Player control

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

#pragma endregion

#pragma region Second Player control

		if (Keyboard::isKeyPressed(Keyboard::I))
		{
			player_2->accelerate(1, -0.08 * time);
		}
		else if (Keyboard::isKeyPressed(Keyboard::L))
		{
			player_2->accelerate(2, 0.08 * time);
		}
		else if (Keyboard::isKeyPressed(Keyboard::K))
		{
			player_2->accelerate(3, 0.08 * time);
		}
		else if (Keyboard::isKeyPressed(Keyboard::J))
		{
			player_2->accelerate(4, -0.08 * time);
		}
		else player_2->playAnimation = false;

#pragma endregion

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