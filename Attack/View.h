#pragma once

#include "Enemy.h"
#include "Player.h"

View view;

void setViewCoordinates(int sizeX, int sizeY, double x, double y, int index)
{
	if (x < sizeX / 2)
		x = sizeX / 2;

	if (x > mapsWidth[index] * 32 - sizeX / 2 - 32)
		x = mapsWidth[index] * 32 - sizeX / 2 - 32;

	if (y > mapsHeight[index] * 32 - sizeY / 2 - 32)
		y = mapsHeight[index] * 32 - sizeY / 2 - 32;

	if (y < sizeY / 2)
		y = sizeY / 2;

	view.setCenter(float(x), float(y));
}

void resetVillainView(int &sizeX, int &sizeY, float &villainViewX, float &villainViewY, int index)
{
	Enemy::evilTank = { false, NULL, 0 };
	Tank::camera = NotDefined;
	
	view.reset(FloatRect(0, 0, (float)sizeX, (float)sizeY));

	villainViewX = (float)sizeX / 2;
	villainViewY = (float)sizeY / 2;
}
