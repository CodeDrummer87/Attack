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

Air::Air(Animation &a, int X, int Y, int dir_, string name_)
{
	anim = a;
	name = name_;
	x = X;
	y = Y;
	dir = dir_;
	anim.sprite.setPosition(x, y);
	anim.sprite.setScale(1.5f, 1.5f);
	playAnimation = isExist = true;
	status = ALIVE;
}

BombStatus Air::bombStatus = ABOARD;

bool Air::isExistFighter = false;

bool Air::isViewToBomb = false;

bool Air::setCurrentCamera = false;

bool Air::isExplosionBomb = false;

Air* Air::bomb = NULL;

Air::~Air()
{}

void Air::update(double time)
{
	if (name != "explosion")
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

			if (isExplosionBomb)
			{
				isExist = false;
				bombStatus = ABOARD;
				isViewToBomb = false;
				isExistFighter = false;
				Air::setCurrentCamera = true;
				isExplosionBomb = false;
			}

			if (anim.isEnd(time))
			{
				isExplosionBomb = true;
				anim.sprite.setColor(Color::Transparent);
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
			if (attachedObject->isExist)
				attachedObject->isExist = false;

		if (y <= -150)
			isExist = false;
	}
	else
	{
		if (anim.isEnd(time))
		{
			bomb = NULL;
			isExist = false;
		}
	}
}