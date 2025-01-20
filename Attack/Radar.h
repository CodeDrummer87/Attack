#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class Radar : public Entity
{
private:
	GroundVehicle* own;
	int constDir;

	void setCoordinates();

public:

	//.:: Constructor :::::::::::::::::::::::
	Radar();
	Radar(Animation&, GroundVehicle*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Radar();
	
	//.:: Public_methods_of_class :::::::::::
	void update(double);

};
