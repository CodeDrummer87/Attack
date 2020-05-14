#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Animation.h"

void showForeground(int x, int y)
{
	using namespace sf;

	RenderWindow fGround(VideoMode(x, y), "Attack", Style::Fullscreen);

	fGround.setFramerateLimit(60);
	fGround.setMouseCursorVisible(false);

	Music foregroundTheme;
	foregroundTheme.openFromFile("source/sounds/foreground/main_theme.ogg");
	foregroundTheme.setVolume(85.f);
	foregroundTheme.play();

	Font font_1, font_2;
	font_1.loadFromFile("source/fonts/KimberleyCYR_Black.otf");
	font_2.loadFromFile("source/fonts/lik_Ascent_2_starDom.otf");

	vector<Text> textList;

	Text attack("ATTACK", font_2, 250);
	attack.setFillColor(Color::Red);
	attack.setPosition(x/2 - (x/2)/1.5, y/2 - (y/2)/1.5);
	textList.push_back(attack);

	Text subdivision("Subdivision Formation", font_1, 50);
	subdivision.setFillColor(Color::Yellow);
	subdivision.setPosition(x / 2, y / 2 - 100);
	textList.push_back(subdivision);

	Text tank_1("Red TANK", font_2, 45),
		tank_2("Yellow TANK", font_2, 45),
		tank_3("Magenta TANK", font_2, 45),
		tank_4("Cyan TANK", font_2, 45),
		tank_5("Hemo TANK", font_2, 45);

	tank_1.setFillColor(Color::Red);		tank_1.setPosition(x / 2, y / 2);			textList.push_back(tank_1);
	tank_2.setFillColor(Color::Yellow);		tank_2.setPosition(x / 2, y / 2 + 70);		textList.push_back(tank_2);
	tank_3.setFillColor(Color::Magenta);	tank_3.setPosition(x / 2, y / 2 + 140);		textList.push_back(tank_3);
	tank_4.setFillColor(Color::Cyan);		tank_4.setPosition(x / 2, y / 2 + 210);		textList.push_back(tank_4);
	tank_5.setFillColor(Color::Green);		tank_5.setPosition(x / 2, y / 2 + 280);		textList.push_back(tank_5);

	Image iStar;
	iStar.loadFromFile("source/images/lighting_star.png");
	iStar.createMaskFromColor(Color::White);

	Texture tStar;
	tStar.loadFromImage(iStar);

	Animation star(tStar, 0, 0, 55, 45, 0.17, 9);
	star.sprite.setPosition(x/2 - 50, y/2 + 25);

	while(fGround.isOpen())
	{
		Event e;
		while (fGround.pollEvent(e))
		{
			if (e.type = Event::Closed)
				fGround.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape))
				fGround.close();
		}

		star.update(1, true, 0);

		fGround.clear();
		for (auto t : textList)
			fGround.draw(t);
		fGround.draw(star.sprite);
		fGround.display();
	}
}