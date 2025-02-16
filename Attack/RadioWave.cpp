#pragma once

#include "RadioWave.h"

RadioWave::RadioWave()
{}

RadioWave::RadioWave(Animation& a, RadioAntenna* antenna_, string name_)
{
	z_index = (short)6;

	anim = a;
	anim.sprite.setColor(Color::Cyan);
	antenna = antenna_;
	name = name_;

	dir = antenna->dir;
	x = antenna->getCoordX(false);
	y = antenna->getCoordY(false);
	isExist = isPlayAnimation = true;
}

RadioWave::~RadioWave()
{}

void RadioWave::update(double time)
{
	if (isExist)
	{
		x = antenna->getCoordX(false);
		y = antenna->getCoordY(false);

		if (anim.isEnd(time))
			isExist = false;
	}
}
