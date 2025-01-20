#pragma once

#include "Entity.h" 
#include "GroundVehicle.h"
#include "Radar.h"

class RadarSweep : public Entity
{
private:
	Radar* radar;

public:

	//.:: Constructor :::::::::::::::::::::::
	RadarSweep();
	RadarSweep(Animation&, Radar*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~RadarSweep();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
};

