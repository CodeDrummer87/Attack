#pragma once

#include "Entity.h"

class Area : public Entity
{
private:
	Entity *own;
public:
	CircleShape area;
	//.:: Constructors :::::::::::::::::::::
	Area();
	Area(double, double, float, Entity*, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Area();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};