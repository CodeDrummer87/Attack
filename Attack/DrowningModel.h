#pragma once

#include "Entity.h"
#include "GroundVehicle.h"

class DrowningModel : public Entity
{
private:
	GroundVehicle *own;

public:

	//.:: Constructor :::::::::::::::::::::::
	DrowningModel();
	DrowningModel(Animation&, GroundVehicle*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~DrowningModel();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
	void draw(RenderWindow&);

};

