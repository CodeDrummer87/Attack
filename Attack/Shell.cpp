#pragma once

#include "Shell.h"
#include "Animation.h"

Shell::Shell() {}

Shell::Shell(Animation &a, Animation &b, int X, int Y, int dir_)
{
	range = 400;
	dist = 0.0;
	name = "shell";
	anim = a;
	animSpare = b;
	dir = dir_;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	playAnimation = true;
	isExist = true;
	status = ALIVE;
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
		isExist = false;
}
