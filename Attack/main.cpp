#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <iostream>
#include <Windows.h>

#include "Animation.h"
#include "Entity.h"

#include "Tank.h"

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

#pragma endregion

#pragma region Textures | Animations | Sounds

	Texture bTank, yTank;
	bTank.loadFromFile("source/images/models/tanks/players/burgundyTank.png");
	yTank.loadFromFile("source/images/models/tanks/players/yellowTank.png");

	Animation burgundy_tank(bTank, 0, 0, 64, 64, 0.016, 2);
	Animation yellow_tank(yTank, 0, 0, 64, 64, 0.016, 2);

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
		for (auto e : entities)
		{
			e->update(time);
			e->anim.update(time, e->playAnimation, e->dir);
		}

		app.clear();
		//.:: display entities :::
		for (auto e : entities)
			e->draw(app);
		app.display();
	}

	return 0;
}