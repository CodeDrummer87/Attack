#pragma once

#include "RadioAntenna.h"

RadioAntenna::RadioAntenna()
{}

RadioAntenna::~RadioAntenna()
{}

RadioAntenna::RadioAntenna(Animation &a, string name_, bool isPlayAnimation_, GroundVehicle *truck, float size_)
{
	anim = a;
	own = truck;
	name = name_;
	
	isPlayAnimation = isPlayAnimation_;
	isExist = true;

	anim.sprite.setScale(size_, size_);

	dir = own->dir;
	x = own->getCoordX(false);
	y = own->getCoordY(false)+5;

	isChangeRotationDirection = false;
}

void RadioAntenna::update(double time)
{
	if (own->name == "truck")
	{
		switch (own->dir)
		{
		case 1:
			x = own->getCoordX(false);
			y = own->getCoordY(false) + 12.0;
			break;

		case 2:
			x = own->getCoordX(false) - 10.0;
			y = own->getCoordY(false);
			break;

		case 3:
			x = own->getCoordX(false);
			y = own->getCoordY(false) - 12.0;
			break;

		case 4:
			x = own->getCoordX(false) + 10.0;
			y = own->getCoordY(false);
			break;
		}

		//.:: Antenna Rotation :::
		dir++;
		if (dir >= 10000)
			dir = 0;
	}
	else
	{
		isExist = false;
	}
}
