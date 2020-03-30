#pragma once

#include "Shell.h"
#include "Animation.h"

Shell::Shell() {}

Shell::Shell(Animation &a, int X, int Y, int dir_)
{
	range = 400;
	dist = 0.0;
	name = "shell";
	anim = a;
	dir = dir_;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	playAnimation = true;
	isExist = true;
}

Shell::~Shell() {}

void Shell::update(double time)
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
		isExist = false;

	x += dx;
	y += dy;
}
