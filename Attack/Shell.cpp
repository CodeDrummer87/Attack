#pragma once

#include "Shell.h"
#include "Animation.h"

Shell::Shell() {}

Shell::Shell(Animation &a, Animation &b, Player* tank)
{
	tokenId = tank->tokenId;
	range = 400;
	dist = 0.0;
	name = "shell";
	army = tank->army;
	anim = a;
	animSpare = b;
	dir = tank->dir;
	own = tank;
	x = tank->getCoordX(true);
	y = tank->getCoordY(true);
	anim.sprite.setPosition(x, y);
	playAnimation = isExist = true;
	status = ALIVE;
	hitPoints = 0;
	level = tank->level;
}

Shell::~Shell() {}

void Shell::update(double time)
{
	if (status == ALIVE)
	{
		if (dir == 1)
		{
			dx = 0;
			dy = -0.4 * time;
			dist -= dy;
		}
		if (dir == 2)
		{
			dy = 0;
			dx = 0.4 * time;
			dist += dx;
		}
		if (dir == 3)
		{
			dx = 0;
			dy = 0.4 * time;
			dist += dy;
		}
		if (dir == 4)
		{
			dy = 0;
			dx = -0.4 * time;
			dist -= dx;
		}

		if (abs(dist) >= range)
		{
			status = WOUNDED;
			anim = animSpare;
			dir = rand() % 360;
		}

		x += dx;
		y += dy;
	}
	else if (status == WOUNDED)
	{
		if (anim.isEnd(time))
			status = DEAD;
	}
	else
	{
		isExist = false;
		own->isShot = true;
	}
}

void Shell::allowShot()
{
	own->isShot = true;
}

void Shell::grantAccess()
{
	own->nickDown();
}
