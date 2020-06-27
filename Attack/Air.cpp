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

bool Air::isExistFighter = false;

bool Air::isViewToBomb = false;

bool Air::setCurrentCamera = false;

Air* Air::bomb = NULL;

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
		dy = -0.09 * time;

		if (anim.isEnd(time))
		{
			isExist = false;
			bombStatus = ABOARD;
			bomb = NULL;
			isViewToBomb = false;
			isExistFighter = false;
			Air::setCurrentCamera = true;
		}
	}

	x += dx;
	y += dy;

	if (bombStatus == ABOARD)
	{
		if (name == "fighter" && y <= attachedObject->getCoordY(false) + 300)
		{
			bombStatus = DROPPED;
			isViewToBomb = true;
		}
	}

	if (name == "fighter" && y <= attachedObject->getCoordY(false))
		if(attachedObject->isExist)
			attachedObject->isExist = false;

	if (y <= -150)
		isExist = false;
}