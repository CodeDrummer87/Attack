#include "RadarSweep.h"

RadarSweep::RadarSweep()
{}

RadarSweep::RadarSweep(Animation &aRadarSweep, Radar *radar_)
{
	z_index = (short)7;

	anim = aRadarSweep;
	anim.sprite.setColor(Color(14, 153, 20));

	radar = radar_;
	level = 0;
	dir = 90;
	isPlayAnimation = false;
	isExist = true;
	name = "radarSweep";
	status = Status::ALIVE;

	x = radar->getCoordX(false);
	y = radar->getCoordY(false);
}

RadarSweep::~RadarSweep()
{}

void RadarSweep::update(double time)
{
	if (isExist)
	{
		dir++;
		dir = dir >= 360 ? 0 : dir;

		x = radar->getCoordX(false);
		y = radar->getCoordY(false);
	}
}
