#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class Smoke : public Entity
{
public:
	GroundVehicle *own;

	//.:: Constructor :::::::::::::::::::::::
	Smoke();
	Smoke(Animation&, GroundVehicle*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Smoke();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
