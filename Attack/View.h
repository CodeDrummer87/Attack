#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void setViewCoordinates(double y)
{
	if (y > 1610)
		y = 1610;

	if (y < 540)
		y = 540;

	view.setCenter(float(960), float(y));
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