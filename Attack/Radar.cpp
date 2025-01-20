#include "Radar.h"


Radar::Radar()
{}

Radar::Radar(Animation &aRadar_, GroundVehicle *own_)
{
	z_index = (short)7;

	anim = aRadar_;
	own = own_;
	level = 0;
	dir = 0;
	isPlayAnimation = false;
	isExist = true;
	name = "radar";
	status = Status::ALIVE;

	setCoordinates();
}

Radar::~Radar()
{}

void Radar::update(double time)
{
	if (status == Status::ALIVE)
	{
		setCoordinates();
	}
}

void Radar::setCoordinates()
{
	x = own->getCoordX(false);
	y = own->getCoordY(false);
}
