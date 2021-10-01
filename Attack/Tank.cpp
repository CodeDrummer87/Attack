#include "Tank.h"


Tank::Tank()
{}

Tank::Tank(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_, int level_)
	: Entity(anim, x_, y_, name_, dir_, isPlayAnimation_)
{
	aTankExplosion = aExplosion;
	army = army_;
	level = level_;

	status = ALIVE;
	isDestroyed = isTransition = false;
	isShot = true;
	isSmoking = true;
	hitPoints = level + 1;
}

Tank::~Tank()
{}

int Tank::counter = 0;

void Tank::update(double time)
{
	if (isDestroyed)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;
	}
	else
	{
		if (hitPoints > 1)
		{
			if (status != ALIVE)
			{
				status = ALIVE;
				anim.sound.setPitch(0.9f);
			}
		}
		else if (hitPoints == 1)
		{
			if (status != WOUNDED)
			{
				status = WOUNDED;
				anim.sound.setPitch(0.5f);
			}
		}
		else
			status = DEAD;
		//::::::::::::::::::::::::
		if (status == ALIVE)
		{
			x += dx;
			y += dy;
			dx = dy = 0;
		}
		else if (status == WOUNDED)
		{
			x += dx / 1.5;
			y += dy / 1.5;
			dx = dy = 0;
		}
		else
		{
			name = "destroyed";
			isPlayAnimation = true;
			if (isTransition)
			{
				if (anim.isEnd(time))
				{
					anim.frames[0] = IntRect(0, 128, 64, 64);	//.:: Tank skeleton texture coordinates
					anim.sound.stop();
					isDestroyed = true;
				}
			}
			else
			{
				anim = aTankExplosion;
				isTransition = true;
				isSmoking = false;
			}
		}
	}
}
