#include "RadarSweep.h"

RadarSweep::RadarSweep()
{}

RadarSweep::RadarSweep(Animation &aRadarSweep, GroundVehicle *own_)
{
	z_index = (short)7;

	anim = aRadarSweep;
	anim.sprite.setColor(Color(14, 153, 20, 230));

	own = own_;
	level = 0;
	dir = 250;
	isPlayAnimation = false;
	isExist = true;
	name = "radarSweep";
	status = Status::ALIVE;

	x = own->getCoordX(false);
	y = own->getCoordY(false);
}

RadarSweep::~RadarSweep()
{}

void RadarSweep::update(double time)
{
	if (isExist)
	{
		dir+=2;
		dir = dir >= 360 ? 0 : dir;

		x = own->getCoordX(false);
		y = own->getCoordY(false);
	}
}
