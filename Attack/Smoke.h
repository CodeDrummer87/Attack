#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class Smoke : public Entity
{
private:
	short numberOfCannon;

public:
	GroundVehicle *own;

	//.:: Constructor :::::::::::::::::::::::
	Smoke();
	Smoke(Animation&, GroundVehicle*, string);
	Smoke(Animation&, GroundVehicle*, string, short);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Smoke();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void setExplosionVolume();

};
