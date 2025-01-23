#pragma once

#include "Entity.h" 
#include "GroundVehicle.h"

class RadarSweep : public Entity
{
private:
	GroundVehicle* own;

public:

	//.:: Constructor :::::::::::::::::::::::
	RadarSweep();
	RadarSweep(Animation&, GroundVehicle*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~RadarSweep();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
};

