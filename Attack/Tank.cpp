#pragma once

#include "Tank.h"

Tank::Tank()
{}

Tank::Tank(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	SoundBuffer &sExplosion, int expFrameCount, string army_, int level_)
	: GroundVehicle(anim, x_, y_, name_, dir_, isPlayAnimation_, sExplosion, expFrameCount, army_, level_)
{
	z_index = 1;

	isSpeedBonusUp = isShowSpeedBonusAchiev = false;
	isShowSniperAchiev = false;
	isShot = true;

	drownedTanks = 3;
	destValue = (army == "player") ? 5 : 4;

	shellSpeedBonus = 0.0f;
}

Tank::~Tank()
{}

Camera Tank::camera = StartGame;

void Tank::update(double time)
{	
	if (!isDestroyed && status != DEAD && isSpeedBonusUp)
	{
		isSpeedBonusUp = false;
		speedBonus = army == "player" ? speedBonus += 0.12f : speedBonus += 0.5f;
	}

	GroundVehicle::update(time);
}

void Tank::shoveOffTankCarcass(GroundVehicle *d)
{
	if (d->pusher != this)
		d->pusher = this;

	switch (dir)
	{
	case 0:
		if (y <= d->getCoordY(false) + 52 && x > d->getCoordX(false) - 32 && x < d->getCoordX(false) + 32 && y > d->getCoordY(false))
		{
			d->dir = 0;
			dy = army == "player" ? dy / 1.4 : dy;
			d->setCoordY(y - 52);
		}
		break;

	case 90:
		if (x + 52 >= d->getCoordX(false) && y > d->getCoordY(false) - 32 && y < d->getCoordY(false) + 32 && x < d->getCoordX(false))
		{
			d->dir = 90;
			dx = army == "player" ? dx / 1.4 : dx;
			d->setCoordX(x + 52);
		}
		break;

	case 180:
		if (y + 52 >= d->getCoordY(false) && x > d->getCoordX(false) - 32 && x < d->getCoordX(false) + 32 && y < d->getCoordY(false))
		{
			d->dir = 180;
			dy = army == "player" ? dy / 1.4 : dy;
			d->setCoordY(y + 52);
		}
		break;

	case 270:
		if (x < d->getCoordX(false) + 52 && y > d->getCoordY(false) - 32 && y < d->getCoordY(false) + 32 && x > d->getCoordX(false))
		{
			d->dir = 270;
			dx = army == "player" ? dx / 1.4 : dx;
			d->setCoordX(x - 52);
		}
		break;
	}
}
