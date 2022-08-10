#pragma once

#include "CommunicationTruck.h"

CommunicationTruck::CommunicationTruck()
{}

CommunicationTruck::CommunicationTruck(Animation &a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	SoundBuffer &sExplosion_, int expFrameCount, string army_, int lvl, int currentGameTime) 
	: GroundVehicle(a, x_, y_, name_, dir, isPlayAnimation, sExplosion_, expFrameCount, army_, lvl)
{
	z_index = 1;

	isPlayerControl = isAirstrikeRequest =  false;
	nextRequestTime = currentGameTime + 120;
	speedBonus = 0.4f;
}

CommunicationTruck::~CommunicationTruck()
{}

void CommunicationTruck::update(double time)
{
	if (isAirstrikeRequest)
		isAirstrikeRequest = false;

	GroundVehicle::update(time);
}
