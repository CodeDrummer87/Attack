#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class Effect : public Entity
{
private:
	GroundVehicle *own;
	int constDir;
	int transparency;

	void setCoordinates();

public:

	//.:: Constructor :::::::::::::::::::::::
	Effect();
	Effect(Animation&, GroundVehicle*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Effect();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
	void draw(RenderWindow&);

};
