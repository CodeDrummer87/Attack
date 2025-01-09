#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class Mine : public Entity
{
private:
	int damage;

	bool checkMineCollision(GroundVehicle*);

public:

	//.:: Constructor :::::::::::::::::::::::
	Mine();
	Mine(Animation&, GroundVehicle*, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Mine();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	bool isActivatedMine(GroundVehicle*);
	bool exploseMine(GroundVehicle*);
};

