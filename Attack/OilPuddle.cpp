#pragma once

#include "OilPuddle.h"

OilPuddle::OilPuddle()
{}

OilPuddle::OilPuddle(Animation &anim_, double X, double Y, int ownDir, bool isPlayAnimation_, int currentTime)
{
	z_index = 0;

	anim = anim_;
	isExist = true;

	switch (ownDir)
	{
	case 0: x = X; y = Y + 35; break;
	case 90: x = X - 35; y = Y; break;
	case 180: x = X; y = Y - 35; break;
	case 270: x = X + 35; y = Y; break;
	}

	number = ++puddleCounter;
	name = "puddle";
	dir = rand() % 360;
	isPlayAnimation = isPlayAnimation_;

	status = ALIVE;
	isAdsorption = false;
	adsorptionTime = currentTime + 40;
	anim.sound.setLoop(false);
	level = 1;
}

OilPuddle::~OilPuddle()
{}

int OilPuddle::puddleCounter = 0;

void OilPuddle::update(double time)
{
	if (isExist)
	{
		if (status == ALIVE && anim.isEnd(time))
		{
			status = WOUNDED;
			isPlayAnimation = false;
			anim.setFrames(0, 64, 64, 64, 1, anim.speed);
			anim.sound.setVolume(0.f);
		}
		else if (status == WOUNDED && isAdsorption)
		{
			status = DEAD;
			isPlayAnimation = true;
			anim.speed = 0.001;
			anim.setFrames(0, 128, 64, 64, 7, anim.speed);
		}
		else if (status == DEAD)
		{
			if (level == 2)
				isExist = false;

			if (anim.isEnd(time))
			{
				anim.sprite.setColor(Color::Transparent);
				level = 2;
			}
		}
	}
}
