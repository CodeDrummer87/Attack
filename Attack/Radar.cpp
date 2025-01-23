#include "Radar.h"


Radar::Radar()
{}

Radar::Radar(Animation &aRadar_, RadarSweep *radarSweep_)
{
	z_index = (short)7;

	anim = aRadar_;
	anim.sound.setVolume(100.f);
	radarSweep = radarSweep_;
	level = 0;
	dir = 0;
	isPlayAnimation = true;
	isExist = true;
	name = "radar";
	status = Status::ALIVE;

	setCoordinates();
}

Radar::~Radar()
{}

void Radar::update(double time)
{
	if (isExist)
	{
		if (anim.isEnd(time))
		{
			isExist = radarSweep->isExist = false;
		}

		setCoordinates();
	}
}

void Radar::setCoordinates()
{
	x = radarSweep->getCoordX(false);
	y = radarSweep->getCoordY(false);
}
