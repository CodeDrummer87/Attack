#pragma once

#include "OilPuddle.h"

OilPuddle::OilPuddle()
{}

OilPuddle::OilPuddle(Animation &anim_, double X, double Y, int ownDir, bool isPlayAnimation_, int currentTime)
{
	anim = anim_;
	isExist = true;
	z_index = 0;

	switch (ownDir)
	{
	case 1: x = X; y = Y + 35; break;
	case 2: x = X - 35; y = Y; break;
	case 3: x = X; y = Y - 35; break;
	case 4: x = X + 35; y = Y; break;
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
			anim.frames[0] = IntRect(0, 64, 64, 64);
			anim.sound.setVolume(0.f);
		}
		else if (status == WOUNDED && isAdsorption)
		{
			status = DEAD;
			isPlayAnimation = true;
			anim.setFrames(0, 128, 64, 64, 7);
			anim.speed = 0.001;
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
