#pragma once

#include "TankTower.h"

TankTower::TankTower()
{}

TankTower::TankTower(Animation &a, double x_, double y_, int dir_, SoundBuffer &sExplosion_, int expFrameCount, GroundVehicle *own_)
	: GroundVehicle(a, x_, y_, "turret", dir_, false, sExplosion_, expFrameCount, "enemy", own_->level)
{
	z_index = 3;
	own = own_;
}

TankTower::~TankTower()
{}

void TankTower::update(double time)
{
	if (isDestroyed)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;
	}
	else
	{
		if (status != DEAD)
		{
			x = own->getCoordX(false);
			y = own->getCoordY(false);

			dir++;
			dir = dir == 1 ? 0 : dir == 2 ? 90 : dir == 3 ? 180 : dir == 4 ? 270 : dir;
		}

		if (!own->isExist)
			isExist = false;

		if (own->status == WOUNDED && status != WOUNDED)
		{
			status = WOUNDED;
			anim.setFrames(0, 128, 128, 128, 1, 1);
			anim.sound.setPitch(0.5f);
		}

		if (own->status == DEAD && status != DEAD)
			status = DEAD;

		if (status == DEAD)
		{
			if (isTransition)
			{
				if (anim.isEnd(time))
				{
					anim.frames[0] = IntRect(0, 384, 128, 128);
					anim.sound.stop();
					isDestroyed = true;
				}
				else
				{
					dir++;
					x += 0.4;
					y -= 0.4;
				}
			}
			else
			{
				name = "destroyed";
				isPlayAnimation = true;
				anim.setFrames(0, 256, 128, 128, 11, 0.008);
				isTransition = true;
			}
		}
	}
}
