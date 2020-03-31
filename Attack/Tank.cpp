#pragma once

#include "Tank.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Tank::Tank() {}

Tank::Tank(Animation &a, Animation &b, Animation &c, int X, int Y, int dir_, string name_)
{
	name = name_;
	dir = dir_;
	anim = a;
	animSpare = b;
	inFlame = c;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	status = ALIVE;
	destroyed = transition = playAnimation = false;
	isExist = true;
}

Tank::~Tank() {}

void Tank::update(double time)
{
	if (destroyed)
	{
		anim.switchSound(false);
	}
	else
	{
		if (status == ALIVE)
		{
			x += dx;
			y += dy;
			dx = dy = 0;
		}
		else if (status == DEAD)
		{
			playAnimation = true;
			if(transition)
			{
				if (anim.isEnd(time))
				{
					anim = inFlame;
					destroyed = true;
				}
			}
			else
			{			
				anim = animSpare;
				transition = true;
			}
		}
	}
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