#pragma once

#include "Entity.h"
#include "GroundVehicle.h"
#include "RadarSweep.h"

class Radar : public Entity
{
private:
	RadarSweep* radarSweep;

	void setCoordinates();

public:

	//.:: Constructor :::::::::::::::::::::::
	Radar();
	Radar(Animation&, RadarSweep*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Radar();
	
	//.:: Public_methods_of_class :::::::::::
	void update(double);

};
