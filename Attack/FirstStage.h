#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

const int H = 68;
const int W = 121;

String FirstStage[H] = 
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"B                                                                                                                      B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"//68
};

RectangleShape rectangle(Vector2f(16, 16));

void drawMap(String map[H], RenderWindow &app, RectangleShape rec)
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'B')
				rec.setFillColor(Color::Green);
			if (map[i][j] == ' ')
				continue;

			rec.setPosition(j * 16, i * 16);
			app.draw(rec);
		}
}