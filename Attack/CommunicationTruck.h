#pragma once

#include "GroundVehicle.h"

class CommunicationTruck : public GroundVehicle
{
public:
	int nextRequestTime;
	bool isAirstrikeRequest;

	//.:: Constructor :::::::::::::::::::::::
	CommunicationTruck();
	CommunicationTruck(Animation&, double, double, string, int, bool, Animation&, string, int, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~CommunicationTruck();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);

};
