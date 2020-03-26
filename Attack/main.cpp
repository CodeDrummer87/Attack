#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>

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

	Texture t;
	t.loadFromFile("images/models/tanks/players/burgundyTank.png");

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 64, 64));
	s.setPosition(500, 250);

	float currentFrame = 0;

	Clock clock;

	while (app.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time /= 1700;

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			s.move(-0.1 * time, 0);

			currentFrame += 0.05 * time;
			if (currentFrame > 2) currentFrame -= 2;
			s.setTextureRect(IntRect(64 + 64, 64 * int(currentFrame), -64, 64));
		}

		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			s.move(+0.1 * time, 0);

			currentFrame += 0.05 * time;
			if (currentFrame > 2) currentFrame -= 2;
			s.setTextureRect(IntRect(64, 64 * int(currentFrame), 64, 64));
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			s.move(0, -0.1 * time);

			currentFrame += 0.05 * time;
			if (currentFrame > 2) currentFrame -= 2;
			s.setTextureRect(IntRect(0, 64 * int(currentFrame), 64, 64));
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			s.move(0, +0.1 * time);

			currentFrame += 0.05 * time;
			if (currentFrame > 2) currentFrame -= 2;
			s.setTextureRect(IntRect(0, 64 * int(currentFrame) + 64, 64, -64));
		}


		app.clear();
		app.draw(s);
		app.display();
	}

	return 0;
}