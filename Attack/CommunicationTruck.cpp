#include "CommunicationTruck.h"

CommunicationTruck::CommunicationTruck()
{}

CommunicationTruck::CommunicationTruck(Animation &a, double x_, double y_, SoundBuffer &sExplosion_, int currentGameTime) 
	: GroundVehicle(a, x_, y_, "truck", 270, false, sExplosion_, 14, "enemy", 1)
{
	z_index = (short)2;

	isPlayerControl = isAirstrikeRequest =  false;
	nextRequestTime = currentGameTime + 120;
	speedBonus = 0.4f;
	isInRadarCoverageArea = false;

	antenna = NULL;
}

CommunicationTruck::~CommunicationTruck()
{}

void CommunicationTruck::update(double time)
{
	if (isAirstrikeRequest)
		isAirstrikeRequest = false;

	if (status != Status::DEAD)
	{
		z_index = isInRadarCoverageArea ? 3 : 2;
		anim.sprite.setColor(isInRadarCoverageArea ? Color(0, 255, 0, 210) : Color::White);
	}

	GroundVehicle::update(time);
}
