#pragma once

#include "GroundVehicle.h"

extern View view;

GroundVehicle::GroundVehicle()
{}

GroundVehicle::GroundVehicle(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_, int level_)
	: Entity(anim, x_, y_, name_, dir_, isPlayAnimation_)
{
	army = army_;
	level = level_;
	status = ALIVE;
	aVehicleExplosion = aExplosion;

	isDestroyed = isTransition = isSmoking = false;
	hitPoints = level + 1;
	toUp = toDown = toRight = toLeft = 0;

	traffic.up.dir = true;		traffic.up.barId = 0;
	traffic.right.dir = true;	traffic.right.barId = 0;
	traffic.down.dir = true;	traffic.down.barId = 0;
	traffic.left.dir = true;	traffic.left.barId = 0;

	number = ++counter;
}

GroundVehicle::~GroundVehicle()
{}

int GroundVehicle::counter = 0;

void GroundVehicle::update(double time)
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
				anim = aVehicleExplosion;
				isTransition = true;
				isSmoking = false;
			}
		}
	}

}

void GroundVehicle::accelerate(int dir_, double acc)
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

bool GroundVehicle::makeSureDestroyed()
{
	return isDestroyed;
}

void GroundVehicle::checkVehiclesCollision(GroundVehicle *t)
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

bool GroundVehicle::makeSureVehicleCollision(GroundVehicle *t)
{
	switch (dir)
	{
	case 1:
		if (y <= t->y + 52 && x > t->x - 32 && x < t->x + 32 && y > t->y)
			return true;

	case 2:
		if (x + 52 >= t->x && y > t->y - 32 && y < t->y + 32 && x < t->x)
			return true;

	case 3:
		if (y + 52 >= t->y && x > t->x - 32 && x < t->x + 32 && y < t->y)
			return true;

	case 4:
		if (x <= t->x + 52 && y > t->y - 32 && y < t->y + 32 && x > t->x)
			return true;
	}

	return false;
}

void GroundVehicle::getAreaDamage(Area *area, string *map)
{
	FloatRect a = this->anim.sprite.getGlobalBounds();
	FloatRect b = area->area.getGlobalBounds();

	if (a.intersects(b))
		if (this->hitPoints > 0)
		{
			this->hitPoints = 0;
			if (area->army != army)
			{
				area->victims++;
				area->totalExperience += this->level;
			}
		}

	if (!area->isTerrainDestroyed)
	{
		area->isTerrainDestroyed = true;
		for (int i = b.top / 32 - b.height / 1.1 / 32; i < b.top / 32 + b.height / 1.1 / 32; i++)
			for (int j = b.left / 32 - b.width / 15 / 32; j < b.left / 32 + b.width / 32; j++)
			{
				if (i > 0 && j > 0)
					if (map[i][j] == 'b' || map[i][j] == 'F')
						map[i][j] = ' ';
			}
	}
}
