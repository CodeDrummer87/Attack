#pragma once

#include "RadioWave.h"

RadioWave::RadioWave()
{}

RadioWave::RadioWave(Animation &a, GroundVehicle *vehicle, string name_)
{
	anim = a;
	anim.sprite.setColor(Color::Cyan);
	own = vehicle;
	name = name_;

	dir = own->dir;
	x = own->getCoordX(false);
	y = own->getCoordY(false);
	isExist = isPlayAnimation = true;
}

RadioWave::~RadioWave()
{}

void RadioWave::update(double time)
{
	if (isExist)
	{
		x = own->getCoordX(false);
		y = own->getCoordY(false);

		if (anim.isEnd(time))
			isExist = false;
	}
}
