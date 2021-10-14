#pragma once

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
	isSmoking = false;
	hitPoints = level +1;
	toUp = toDown = toRight = toLeft = 0;

	traffic.up.dir = true;		traffic.up.barId = 0;
	traffic.right.dir = true;	traffic.right.barId = 0;
	traffic.down.dir = true;	traffic.down.barId = 0;
	traffic.left.dir = true;	traffic.left.barId = 0;

	number = ++counter;
}

Tank::~Tank()
{}

int Tank::counter = 0;
Camera Tank::camera = StartGame;

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

void Tank::accelerate(int dir_, double acc)
{
	isPlayAnimation = true;
	dir = dir_;

	switch (dir)
	{
	case 1:
		toLeft = toRight = 0;
		if (traffic.up.dir)
			toUp = acc - ((double)level / 100);
		else
			toUp = 0;
		break;

	case 2:
		toUp = toDown = 0;
		if (traffic.right.dir)
			toRight = acc + ((double)level / 100);
		else
			toRight = 0;
		break;

	case 3:
		toLeft = toRight = 0;
		if (traffic.down.dir)
			toDown = acc + ((double)level / 100);
		else
			toDown = 0;
		break;

	case 4:
		toUp = toDown = 0;
		if (traffic.left.dir)
			toLeft = acc - ((double)level / 100);
		else
			toLeft = 0;
		break;
	}

	dx += toLeft + toRight;
	dy += toUp + toDown;
	toUp = toRight = toDown = toLeft = 0;
}

bool Tank::makeSureDestroyed()
{
	return isDestroyed;
}

void Tank::checkMapCollision(string map[])
{
	for (int i = (anim.getRect(dir).top + 15) / 32; i < (y + anim.getRect(dir).height) / 32; i++)
		for (int j = (anim.getRect(dir).left + 14) / 32; j < (x + anim.getRect(dir).width) / 32; j++)
		{
			if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
			{
				if (i * 32 < y && j * 32 > x - 26 && j * 32 < x + 26)
				{
					if (dy < 0)
						dy = 0.F;
				}

				if (i * 32 > y && j * 32 > x - 26 && j * 32 < x + 26)
				{
					if (dy > 0)
						dy = 0.F;
				}

				if (j * 32 > x && i * 32 > y - 26 && i * 32 < y + 26)
				{
					if (dx > 0)
						dx = 0.F;
				}

				if (j * 32 < x && i * 32 > y - 26 && i * 32 < y + 26)
				{
					if (dx < 0)
						dx = 0.F;
				}
			}
		}
}
