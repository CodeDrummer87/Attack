#pragma once

#include "RadioAntenna.h"

RadioAntenna::RadioAntenna()
{}

RadioAntenna::~RadioAntenna()
{}

RadioAntenna::RadioAntenna(Animation &a, GroundVehicle *truck)
{
	z_index = (short)2;

	anim = a;
	own = truck;
	name = "antenna";
	
	isPlayAnimation = false;
	isExist = true;

	anim.sprite.setScale(1.8f, 1.8f);

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
		case 0:
			x = own->getCoordX(false);
			y = own->getCoordY(false) + 12.0;
			break;

		case 90:
			x = own->getCoordX(false) - 10.0;
			y = own->getCoordY(false);
			break;

		case 180:
			x = own->getCoordX(false);
			y = own->getCoordY(false) - 12.0;
			break;

		case 270:
			x = own->getCoordX(false) + 10.0;
			y = own->getCoordY(false);
			break;
		}

		//.:: Antenna Rotation :::
		dir++;
		resetDegrees(dir);
	}
	else
	{
		isExist = false;
	}
}
