#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void setViewCoordinates(int sizeX, int sizeY, double x, double y)
{
	if (x < sizeX / 2)
		x = sizeX / 2;

	if (x > W * 32 - sizeX / 2 - 32)
		x = W * 32 - sizeX / 2 - 32;

	if (y > H * 32 - sizeY / 2 - 32)
		y = H * 32 - sizeY / 2 - 32;

	if (y < sizeY / 2)
		y = sizeY / 2;

	view.setCenter(float(x), float(y));
}

void defineNewCommander(vector<Player*> team)
{
	Player* newCommander = team[0];
	int lvl = 0;

	for (auto p : team)
	{
		if (p->status != DEAD && !p->isCommander)
		{
			if (p->level > lvl)
			{
				newCommander = p;
				lvl = p->level;
			}
		}
	}

	newCommander->isCommander = true;
}