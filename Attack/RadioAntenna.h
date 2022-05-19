#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class RadioAntenna : public Entity
{
private:
	GroundVehicle *own;
	bool isChangeRotationDirection;

public:

	//.:: Constructor :::::::::::::::::::::::
	RadioAntenna();
	RadioAntenna(Animation&, string, bool, GroundVehicle*, float);
	
	//.:: Destructor ::::::::::::::::::::::::
	virtual ~RadioAntenna();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);

};

