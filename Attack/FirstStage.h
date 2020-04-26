#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

const int H = 34;
const int W = 61;

String FirstStage[H] = 
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B   BBBBBBBBBB     WWWWWWWWWWWWWWWWWWWWWWW     BBBBBBBBBB   B",
	"BbbbWWWWFFFFFF     WWWWWWWWWWWWWWWWWWWWWWW     FFFFFFWWWWbbbB",
	"BbbbWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFWWWWbbbB",
	"BbbbWWWWbbbbFFFFFF        bbbbbbb          FFFFFFbbbbWWWWbbbB",
	"BbbbWWWWbbbbFFFFFF   R    bbbUbbb    R     FFFFFFbbbbWWWWbbbB",
	"BbbbWWWWbbbWWWWWWWbb      bbbbbbb        bbWWWWWWWbbbWWWWbbbB",
	"BbbbWWWWbUbWWWWWWWbb      bbbbbbb        bbWWWWWWWbUbWWWWbbbB",
	"B                            B                              B",
	"B                           UBU                             B",
	"B            BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB             B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"BWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
	"BWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBFFFFFFBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"BBBBBBBBBBBWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWBBBBBBBBBBB",
	"BBBBBBBBBBWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWBBBBBBBBBB",
	"BBBBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBBBBB",
	"BBBBBBBBFFFFFFFFFbbbbbbbbbbbbbbbbbbbbbbbbbbbFFFFFFFFFBBBBBBBB",
	"BBBBBBBFFFFFFFFbbbbb                     bbbbbFFFFFFFFBBBBBBB",
	"BBBBBBFFFFFFFbbbbbbb                     bbbbbbbFFFFFFFBBBBBB",
	"BBBBBFFFFFFFbbbbbb                         bbbbbbFFFFFFFBBBBB",
	"BBBBFFFFFFFbbbbbbb                         bbbbbbbFFFFFFFBBBB",
	"BBBFFFFFFFbbbbbb                             bbbbbbFFFFFFFBBB",
	"BBFFFFFFFbbbbbbb                             bbbbbbbFFFFFFFBB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

RectangleShape rectangle(Vector2f(32, 32));

void drawMap(String map[H], RenderWindow &app, Animation &a, double time)
{
	a.update(time, true, 1);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'W')
				a.sprite.setTextureRect(a.frames[(int)a.frame]);
			if (map[i][j] == 'B')
				a.sprite.setTextureRect(IntRect(0, 32, 32, 32));
			if (map[i][j] == 'b')
				a.sprite.setTextureRect(IntRect(96, 32, 32, 32));
			if (map[i][j] == 'U')
				a.sprite.setTextureRect(IntRect(128, 32, 32, 32));
			if (map[i][j] == ' ' || map[i][j] == 'F' || map[i][j] == 'R')
				continue;

			a.sprite.setPosition(j * 32, i * 32);
			app.draw(a.sprite);
		}
}

void drawForestAndIcons(String map[H], RenderWindow &app, Animation &a, Animation &aIcon, double time)
{
	aIcon.update(time, true, 1);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'F')
			{
				a.sprite.setTextureRect(IntRect(32, 32, 32, 32));
				a.sprite.setPosition(j * 32, i * 32);
				app.draw(a.sprite);
			}

			if (map[i][j] == 'R')
			{
				aIcon.sprite.setTextureRect(aIcon.frames[(int)aIcon.frame]);
				aIcon.sprite.setPosition(j * 32, i * 32);
				app.draw(aIcon.sprite);
			}
		}
}