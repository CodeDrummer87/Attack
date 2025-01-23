#pragma once

#include "GroundVehicle.h"

class CommunicationTruck : public GroundVehicle
{
public:
	bool isAirstrikeRequest;
	bool isInRadarCoverageArea;

	//.:: Constructor :::::::::::::::::::::::
	CommunicationTruck();
	CommunicationTruck(Animation&, double, double, SoundBuffer&, int, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~CommunicationTruck();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);

};
