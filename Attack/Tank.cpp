#pragma once

#include "Tank.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Tank::Tank() {}

Tank::~Tank() {}

void Tank::update(double time)
{
	x += dx;
	y += dy;
	dx = dy = 0;
}

void Tank::accelerate(int dir_, double acc)
{
	playAnimation = true;
	dir = dir_;

	if (dir % 2 == 0)
	{
		dy = 0;
		dx = acc;
	}
	else
	{
		dx = 0;
		dy = acc;
	}
}