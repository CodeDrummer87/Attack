#pragma once

#include "Tank.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Tank::Tank() {}

Tank::Tank(Animation &a, Animation &b, int X, int Y, int dir_, string army_)
{
	tokenId = ++counter;
	name = "tank";
	army = army_;
	dir = dir_;
	anim = a;
	aTankExplosion = b;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	status = ALIVE;
	isSmoking = destroyed = transition = playAnimation = false;
	isExist = true;
	
	traffic.up.dir = true;	traffic.up.barId = 0;
	traffic.right.dir = true;	traffic.right.barId = 0;
	traffic.down.dir = true;	traffic.down.barId = 0;
	traffic.left.dir = true;	traffic.left.barId = 0;
}

Tank::~Tank() {}

void Tank::update(double time)
{
	if (destroyed)
	{
		if(playAnimation)
			playAnimation = false;
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
			name = "destroyed";
			playAnimation = true;
			if(transition)
			{
				if (anim.isEnd(time))
				{
					anim.frames[0] = IntRect(0, 128, 64, 64);	//.:: Tank skeleton texture coordinates
					anim.switchSound(false);
					destroyed = true;
				}
			}
			else
			{			
				anim = aTankExplosion;
				transition = true;
			}
		}
	}
}

void Tank::accelerate(int dir_, double acc)
{
	playAnimation = true;
	dir = dir_;

	switch (dir)
	{
	case 1:
		toLeft = toRight = 0;
		if (traffic.up.dir)
			toUp = acc;
		else
			toUp = 0;
		break;

	case 2:
		toUp = toDown = 0;
		if (traffic.right.dir)
			toRight = acc;
		else
			toRight = 0;
		break;

	case 3:
		toLeft = toRight = 0;
		if (traffic.down.dir)
			toDown = acc;
		else
			toDown = 0;
		break;

	case 4:
		toUp = toDown = 0;
		if (traffic.left.dir)
			toLeft = acc;
		else
			toLeft = 0;
		break;
	}

	dx += toLeft + toRight;
	dy += toUp + toDown;
	toUp = toRight = toDown = toLeft = 0;
}