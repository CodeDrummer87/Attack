#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

const int H = 34;
const int W = 61;

String FirstStage[H] = 
{
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"                                                             ",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBFFFFFFBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"BBBBBBBBBBBWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWBBBBBBBBBBB",
	"BBBBBBBBBBWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWBBBBBBBBBB",
	"BBBBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBBBBB",
	"BBBBBBBBFFFFFFFFF                           FFFFFFFFFBBBBBBBB",
	"BBBBBBBFFFFFFFF                               FFFFFFFFBBBBBBB",
	"BBBBBBFFFFFFF                                   FFFFFFFBBBBBB",
	"BBBBBFFFFFFF                                     FFFFFFFBBBBB",
	"BBBBFFFFFFF                                       FFFFFFFBBBB",
	"BBBFFFFFFF                                         FFFFFFFBBB",
	"BBFFFFFFF                                           FFFFFFFBB",
	"BFFFFFFF                                             FFFFFFFB"
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
			if (map[i][j] == 'F')
				a.sprite.setTextureRect(IntRect(32, 32, 32, 32));
			if (map[i][j] == 'B')
				a.sprite.setTextureRect(IntRect(0, 32, 32, 32));
			if (map[i][j] == ' ')
				continue;

			a.sprite.setPosition(j * 32, i * 32);
			app.draw(a.sprite);
		}
}