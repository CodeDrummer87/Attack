#pragma once

#include "Air.h"
#include "GroundVehicle.h"

class RadioWave : public Air
{
private:
	GroundVehicle *own;

public:

	//.:: Constructor :::::::::::::::::::::::
	RadioWave();
	RadioWave(Animation&, GroundVehicle*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~RadioWave();

	//.:: Methods_of_class  :::::::::::::::::
	void update(double);
};

