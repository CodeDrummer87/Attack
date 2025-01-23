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
	RadioAntenna(Animation&, GroundVehicle*);
	
	//.:: Destructor ::::::::::::::::::::::::
	virtual ~RadioAntenna();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);

};

