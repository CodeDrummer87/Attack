#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Animation.h"
#include "Entity.h"

#include "Tank.h"

using namespace std;
using namespace sf;

int main()
{
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

	Texture bTank, yTank;
	bTank.loadFromFile("images/models/tanks/players/burgundyTank.png");
	yTank.loadFromFile("images/models/tanks/players/yellowTank.png");

	Animation burgundy_tank(bTank, 0, 0, 64, 64, 0.016, 2);
	Animation yellow_tank(yTank, 0, 0, 64, 64, 0.016, 2);

	Tank *tank = new Tank();
	tank->setEntity(burgundy_tank, 960, 800);

	Tank *player_2= new Tank();
	player_2->setEntity(yellow_tank, 960, 900);

	vector<Entity*> entities;
	entities.push_back(tank);
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

		if (Keyboard::isKeyPressed(Keyboard::Up))
			tank->accelerate(1, -0.08 * time);

		if (Keyboard::isKeyPressed(Keyboard::Right))
			tank->accelerate(2, 0.08 * time);

		if (Keyboard::isKeyPressed(Keyboard::Down))
			tank->accelerate(3, 0.08 * time);

		if (Keyboard::isKeyPressed(Keyboard::Left))
			tank->accelerate(4, -0.08 * time);

		//.:: update entities :::
		for (auto e : entities)
		{
			e->update(time);
			e->anim.update(time);
		}

		app.clear();
		//.:: display entities :::
		for (auto e : entities)
			e->draw(app);
		app.display();
	}

	return 0;
}