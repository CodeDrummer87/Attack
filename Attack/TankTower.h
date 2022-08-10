#pragma once

#include "GroundVehicle.h"

class TankTower : public GroundVehicle
{
private:
	GroundVehicle *own;

public:

	//.:: Constructor :::::::::::::::::::::::
	TankTower();
	TankTower(Animation&, double, double, int, SoundBuffer&, int, GroundVehicle*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~TankTower();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
