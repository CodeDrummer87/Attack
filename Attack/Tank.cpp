#pragma once

#include "Tank.h"
#include "GroundVehicle.h"

Tank::Tank()
{}

Tank::Tank(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_, int level_)
	: GroundVehicle(anim, x_, y_, name_, dir_, isPlayAnimation_, aExplosion, army_, level_)
{
	isDrowned = drowning = isSpeedBonusUp = false;
	isShowSpeedBonusAchiev = isShowSniperAchiev = false;
	isShot = true;
	pusher = NULL;

	drownedTanks = 3;
	speedBonus = 0.0f;
	destValue = (army == "player") ? 5 : 4;

	shellSpeedBonus = 0.0f;
}

Tank::~Tank()
{}

Camera Tank::camera = StartGame;

void Tank::update(double time)
{
	GroundVehicle::update(time);
	
	if (!isDestroyed && status != DEAD && isSpeedBonusUp)
	{
		isSpeedBonusUp = false;
		speedBonus = army == "player" ? speedBonus += 0.12f : speedBonus += 0.3f;
	}
}

void Tank::accelerate(int dir_, double acc)
{
	acc = (acc > 0) ? acc + speedBonus : acc - speedBonus;
	GroundVehicle::accelerate(dir_, acc);
}

void Tank::shoveOffTankCarcass(Tank *d)
{
	if (d->pusher != this)
		d->pusher = this;

	switch (dir)
	{
	case 1:
		if (y <= d->y + 52 && x > d->x - 32 && x < d->x + 32 && y > d->y)
		{
			d->dir = 1;
			dy /= 1.4;
			d->y = y - 52;
		}
		break;

	case 2:
		if (x + 52 >= d->x && y > d->y - 32 && y < d->y + 32 && x < d->x)
		{
			d->dir = 2;
			dx /= 1.4;
			d->x = x + 52;
		}
		break;

	case 3:
		if (y + 52 >= d->y && x > d->x - 32 && x < d->x + 32 && y < d->y)
		{
			d->dir = 3;
			dy /= 1.4;
			d->y = y + 52;
		}
		break;

	case 4:
		if (x < d->x + 52 && y > d->y - 32 && y < d->y + 32 && x > d->x)
		{
			d->dir = 4;
			dx /= 1.4;
			d->x = x - 52;
		}
		break;
	}
}

void Tank::sinkTheTankCarcass(string *map)
{
	int i = y/32;
	int j = x/32;

	switch (dir)
	{
	case 1: i++; break;
	case 4: j++; break;
	}

	if (map[i][j] == 'W')
	{
		if (pusher != NULL && pusher->destValue != 0)
		{
			pusher->drownedTanks++;
			if (pusher->drownedTanks >= pusher->destValue)
			{
				pusher->isSpeedBonusUp = pusher->isShowSpeedBonusAchiev = true;

				if (pusher->army == "player")
					pusher->destValue = pusher->destValue < 80 ? pusher->destValue * 2 : 0;
				else
					pusher->drownedTanks = 3;
			}
			pusher = NULL;
		}

		anim.sprite.setColor(Color::Transparent);
		this->isDrowned = true;
	}
}
