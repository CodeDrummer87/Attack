#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class Mine : public Entity
{
public:

	//.:: Constructor :::::::::::::::::::::::
	Mine();
	Mine(Animation&, GroundVehicle*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Mine();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
};

