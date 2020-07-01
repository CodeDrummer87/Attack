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

bool checkTeamForCommander(vector<Player*> team)
{
	for (auto p : team)
	{
		if (p->isCommander)
			return true;
	}

	return false;
}

void resetVillainView(Enemy *e, int &sizeX, int &sizeY, vector<Player*> team, float &villainViewX, float &villainViewY)
{
	e->isVillain = Tank::cameraIsNotFree = false;
	view.reset(FloatRect(0, 0, (float)sizeX, (float)sizeY));
	e->finishVillainTime = 0;
	if (!checkTeamForCommander(team))
		view.setCenter(W * 32 / 2 - 16, H * 32 - sizeY / 2 - 32);

	villainViewX = (float)sizeX / 2;
	villainViewY = (float)sizeY / 2;
}