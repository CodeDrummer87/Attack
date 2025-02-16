#pragma once

#include "GroundVehicle.h"
#include "RadioAntenna.h"

class CommunicationTruck : public GroundVehicle
{
public:
	bool isAirstrikeRequest;
	bool isInRadarCoverageArea;

	RadioAntenna* antenna;

	//.:: Constructor :::::::::::::::::::::::
	CommunicationTruck();
	CommunicationTruck(Animation&, double, double, SoundBuffer&, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~CommunicationTruck();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);

};
