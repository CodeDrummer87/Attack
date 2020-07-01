#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Animation.h"

void showForeground(int x, int y, bool &game, int &numberOfPlayers, Sound &start)
{
	using namespace sf;

	RenderWindow *fGround = new RenderWindow(VideoMode(x, y), "Attack", Style::Fullscreen);

	fGround->setVerticalSyncEnabled(true);
	fGround->setMouseCursorVisible(false);
	fGround->setKeyRepeatEnabled(false);

	SoundBuffer choiceBuf, screamBuf;
	choiceBuf.loadFromFile("source/sounds/foreground/choose_number_of_players.ogg");
	screamBuf.loadFromFile("source/sounds/foreground/scream.ogg");

	Sound *choice = new Sound(choiceBuf), *scream = new Sound(screamBuf);

	Font font_1, font_2;
	font_1.loadFromFile("source/fonts/KimberleyCYR_Black.otf");
	font_2.loadFromFile("source/fonts/lik_Ascent_2_starDom.otf");

	vector<Text*> textList;

	int attackSize, subDiv, tankFontSize;
	if (x != 1280 && y != 1024)
	{
		attackSize = 250;
		subDiv = 50;
		tankFontSize = 45;
	}
	else
	{
		attackSize = 200;
		subDiv = 45;
		tankFontSize = 36;
	}

	Text *attack = new Text("ATTACK", font_2, attackSize);
	attack->setFillColor(Color::Red);
	attack->setPosition((float)(x/2 - (x/2)/1.5), (float)(y/2 - (y/2)/1.5));
	textList.push_back(attack);

	Text *subdivision = new Text("Subdivision Formation", font_1, subDiv);
	subdivision->setFillColor(Color::Yellow);
	subdivision->setPosition(x / 2, y / 2 - 100);
	textList.push_back(subdivision);

	Text *tank_1 = new Text("Red TANK", font_2, tankFontSize),
		*tank_2 = new Text("Yellow TANK", font_2, tankFontSize),
		*tank_3 = new Text("Magenta TANK", font_2, tankFontSize),
		*tank_4 = new Text("Cyan TANK", font_2, tankFontSize),
		*tank_5 = new Text("Hemo TANK", font_2, tankFontSize);

	tank_1->setFillColor(Color::Red);		tank_1->setPosition(x / 2, y / 2);			textList.push_back(tank_1);
	tank_2->setFillColor(Color::White);		tank_2->setPosition(x / 2, y / 2 + 70);		textList.push_back(tank_2);
	tank_3->setFillColor(Color::White);		tank_3->setPosition(x / 2, y / 2 + 140);	textList.push_back(tank_3);
	tank_4->setFillColor(Color::White);		tank_4->setPosition(x / 2, y / 2 + 210);	textList.push_back(tank_4);
	tank_5->setFillColor(Color::White);		tank_5->setPosition(x / 2, y / 2 + 280);	textList.push_back(tank_5);

	Text *programmer = new Text("code.drummer87@gmail.com", font_1, 17);
	programmer->setFillColor(Color::Red);
	programmer->setPosition(x - 250, y - 50);
	textList.push_back(programmer);

	Image iStar;
	iStar.loadFromFile("source/images/lighting_star.png");
	iStar.createMaskFromColor(Color::White);

	Texture tStar;
	tStar.loadFromImage(iStar);

	Animation *star = new Animation(tStar, 0, 0, 55, 45, 0.17, 9);
	star->sprite.setPosition(x/2 - 50, y/2 + 25);

	while(fGround->isOpen())
	{
		Event e;
		while (fGround->pollEvent(e))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game = false;
				fGround->close();
				delete choice, star, scream, fGround;
			}

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				start.play();
				fGround->close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (numberOfPlayers <= 4)
				{
					choice->play();
					star->sprite.move(0, 70);
					++numberOfPlayers;
					
					if (numberOfPlayers >= 2)
						tank_2->setFillColor(Color::Yellow);
					if (numberOfPlayers >= 3)
						tank_3->setFillColor(Color::Magenta);
					if (numberOfPlayers >= 4)
						tank_4->setFillColor(Color::Cyan);
					if (numberOfPlayers == 5)
					{
						scream->play();
						tank_5->setFillColor(Color::Green);
					}
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (numberOfPlayers >= 2)
				{
					choice->play();
					star->sprite.move(0, -70);
					--numberOfPlayers;

					if (numberOfPlayers <= 4)
						tank_5->setFillColor(Color::White);
					if (numberOfPlayers <= 3)
						tank_4->setFillColor(Color::White);
					if (numberOfPlayers <= 2)
						tank_3->setFillColor(Color::White);
					if (numberOfPlayers <= 1)
						tank_2->setFillColor(Color::White);
				}
			}
		}
		
		star->update(1, true, 0);

		fGround->clear();
		for (auto t : textList)
			fGround->draw(*t);
		fGround->draw(star->sprite);
		fGround->display();
	}
}