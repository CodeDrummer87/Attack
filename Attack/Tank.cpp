#pragma once

#include "Tank.h"
#include "Enemy.h"

extern View view;

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
	isDestroyed = isTransition = isDrowned = drowning = false;
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
			if (x + dx > 0 && x + dx < 61 * 32)
				x += dx;
			if (y + dy > 0 && y + dy < 119 * 32)
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
				name = "destroyed";
				isPlayAnimation = true;
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
	if (army == "player")
	{
		if (y < view.getCenter().y - 510)
			dy += toDown;
		else if (y > view.getCenter().y + 510)
			dy += toUp;
		else
			dy += toUp + toDown;
	}
	else
		dy += toUp + toDown;
	
	toUp = toRight = toDown = toLeft = 0;
}

bool Tank::makeSureDestroyed()
{
	return isDestroyed;
}

void Tank::checkTanksCollision(Tank *t)
{
	switch (dir)
	{
	case 1:
		if (y <= t->y + 52 && x > t->x - 32 && x < t->x + 32 && y > t->y)
		{
			if (army == "enemy")
			{
				traffic.up.dir = false;
				traffic.up.barId = t->number;
			}
			else
				dy = 0;
		}
		else if (y > t->y + 52 && x > t->x - 32 && x < t->x + 32 && y > t->y)
			if (!traffic.up.dir && traffic.up.barId == t->number && army == "enemy")
			{
				traffic.up.dir = true;
				traffic.up.barId = 0;
			}
		break;

	case 2:
		if (x + 52 >= t->x && y > t->y - 32 && y < t->y + 32 && x < t->x)
		{
			if (army == "enemy")
			{
				traffic.right.dir = false;
				traffic.right.barId = t->number;
			}
			else
				dx = 0;
		}
		else if (x + 52 < t->x && y > t->y - 32 && y < t->y + 32 && x < t->x)
			if (!traffic.right.dir && traffic.right.barId == t->number && army == "enemy")
			{
				traffic.right.dir = true;
				traffic.right.barId = 0;
			}
		break;

	case 3:
		if (y + 52 >= t->y && x > t->x - 32 && x < t->x + 32 && y < t->y)
		{
			if (army == "enemy")
			{
				traffic.down.dir = false;
				traffic.down.barId = t->number;
			}
			else
				dy = 0;
		}
		else if (y + 52 < t->y && x > t->x - 32 && x < t->x + 32 && y < t->y)
			if (!traffic.down.dir && traffic.down.barId == t->number && army == "enemy")
			{
				traffic.down.dir = true;
				traffic.down.barId = 0;
			}
		break;

	case 4:
		if (x <= t->x + 52 && y > t->y - 32 && y < t->y + 32 && x > t->x)
		{
			if (army == "enemy")
			{
				traffic.left.dir = false;
				traffic.left.barId = t->number;
			}
			else
				dx = 0;
		}
		else if (x > t->x + 52 && y > t->y - 32 && y < t->y + 32 && x > t->x)
			if (!traffic.left.dir && traffic.left.barId == t->number && army == "enemy")
			{
				traffic.left.dir = true;
				traffic.left.barId = 0;
			}
		break;
	}
}

void Tank::shoveOffTankCarcass(Tank *d)
{
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
		anim.sprite.setColor(Color::Transparent);
		this->isDrowned = true;
	}
}
