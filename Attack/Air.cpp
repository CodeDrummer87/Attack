#include "Air.h"

Air::Air()
{}

Air::Air(Animation &a, int X, int Y, int dir_, string name_, Entity *currentAirStrikeZone)
{
	anim = a;
	name = name_;
	x = X;
	y = Y;
	dir = dir_;
	anim.sprite.setPosition(x, y);
	playAnimation = isExist = true;
	status = ALIVE;

	attachedObject = currentAirStrikeZone;
}

BombStatus Air::bombStatus = ABOARD;

Air::~Air()
{}

void Air::update(double time)
{
	if (name != "bomb")
	{
		dx = 0;
		dy = -0.7 * time;
	}
	else
	{
		dx = 0;
		dy = -0.05 * time;

		if (anim.isEnd(time))
		{
			isExist = false;
		}
	}

	x += dx;
	y += dy;

	if (bombStatus == ABOARD)
	{
		if (name == "fighter" && y <= attachedObject->getCoordY(false) + 300)
			bombStatus = DROPPED;
	}

	if (name == "fighter" && y <= attachedObject->getCoordY(false))
		if(attachedObject->isExist)
			attachedObject->isExist = false;

	if (y <= -150)
		isExist = false;
}